#include<iostream>
#include<SFML/Graphics.hpp>
#include <cmath>

#include "cellManager.h"

bool sand_select = true, stone_select = false, water_select = false;
sf::Clock _clock;

const float update_frequency = 0.01f; 

float update_timer = update_frequency;


int main() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "falling sand simulation", sf::Style::Close);

	window.setFramerateLimit(120);

	CellManager simulation;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);  // clear the window to black

		sf::Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed) window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				sand_select = true;
				stone_select = false;
				water_select = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ){
				stone_select = true;
				sand_select = false;
				water_select = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
				water_select = true;
				stone_select = false;
				sand_select = false;
			}

			sf::Vector2i _pos = sf::Mouse::getPosition(window);

			int x_pos = floor(_pos.x / simulation.cell_size);
			int y_pos = floor(_pos.y / simulation.cell_size);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				
				if(sand_select) simulation.CreateSand(x_pos, y_pos);
				else if (stone_select) simulation.CreateStone(x_pos, y_pos);
				else if (water_select) simulation.CreateWater(x_pos, y_pos);

			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				simulation.DeleteCell(x_pos, y_pos);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				// clears world
				simulation.Clear();
			}

		}
		float t = _clock.restart().asSeconds();
		update_timer -= t;

		if (update_timer < 0.0f) {
			simulation.Update();
			update_timer = update_frequency;	
		}

		simulation.Draw(window);

		window.display();
	}

	return 0;
}


