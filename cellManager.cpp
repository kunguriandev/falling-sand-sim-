#include "cellManager.h"
#include <iostream>


CellManager::CellManager()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			old_frame_grid[i][j].id = air_id;
			new_frame_grid[i][j].id = air_id;
		}
	}

}

void CellManager::Update()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			if (old_frame_grid[i][j].id == air_id) 	new_frame_grid[i][j].occupied = false;

			if (old_frame_grid[i][j].id == sand_id) update_sand(i, j);
			
			if (old_frame_grid[i][j].id == water_id) update_water(i, j);




		}

	}
}

void CellManager::Draw(sf::RenderWindow& _window)
{

	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{

			if (new_frame_grid[i][j].id == sand_id) {
				sf::RectangleShape _sandShape = sf::RectangleShape();
				_sandShape.setPosition(i * cell_size, j * cell_size);
				_sandShape.setSize(sf::Vector2f(cell_size, cell_size));
				_sandShape.setFillColor(sf::Color::Yellow);

				_window.draw(_sandShape);
			}
			if (new_frame_grid[i][j].id == stone_id) {
				sf::RectangleShape _stoneShape = sf::RectangleShape();
				_stoneShape.setPosition(i * cell_size, j * cell_size);
				_stoneShape.setSize(sf::Vector2f(cell_size, cell_size));
				_stoneShape.setFillColor(sf::Color::White);

				_window.draw(_stoneShape);
			}
			if (new_frame_grid[i][j].id == water_id) {
				sf::RectangleShape _waterShape = sf::RectangleShape();
				_waterShape.setPosition(i * cell_size, j * cell_size);
				_waterShape.setSize(sf::Vector2f(cell_size, cell_size));
				_waterShape.setFillColor(sf::Color::Blue);

				_window.draw(_waterShape);
			}

			old_frame_grid[i][j] = new_frame_grid[i][j];

		}
	}
}

void CellManager::Clear()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			old_frame_grid[i][j].id = air_id;
			new_frame_grid[i][j].id = air_id;
		}
	}
}

void CellManager::CreateSand(int x_pos, int y_pos)
{
	new_frame_grid[x_pos][y_pos].id = sand_id;
}

void CellManager::CreateStone(int x_pos, int y_pos)
{
	new_frame_grid[x_pos][y_pos].id = stone_id;
}

void CellManager::CreateWater(int x_pos, int y_pos)
{
	new_frame_grid[x_pos][y_pos].id = water_id;
}

void CellManager::DeleteCell(int x_pos, int y_pos)
{
	new_frame_grid[x_pos][y_pos].id = air_id;

}

void CellManager::update_sand(int x_pos, int y_pos)
{
		new_frame_grid[x_pos][y_pos].occupied = true;

		bool _downwardLeft = false, _downwardRight = false, _down = false;
	
		if (old_frame_grid[x_pos][y_pos + 1].id == air_id) { // if air below - fall down 
			_down = true;
		}
		if (old_frame_grid[x_pos - 1][y_pos + 1].id == air_id) {
			_downwardLeft = true;
		}
		if (old_frame_grid[x_pos + 1][y_pos + 1].id == air_id) {
			_downwardRight = true;
		}

		if (_downwardLeft && _downwardRight) {
			bool _dir = rand() % 2;
			if (_dir == 0) {
				_downwardLeft = true;
				_downwardRight = false;
			}
			else if (_dir == 1) {
				_downwardLeft = false;
				_downwardRight = true;
			}
		}

		if (old_frame_grid[x_pos][y_pos + 1].id == water_id) {
			new_frame_grid[x_pos][y_pos].id = water_id;
			new_frame_grid[x_pos][y_pos + 1].id = sand_id;
		}

		if (_down) {
			new_frame_grid[x_pos][y_pos].id = air_id;
			new_frame_grid[x_pos][y_pos + 1].id = sand_id;
		}
		else if (_downwardLeft) {
			new_frame_grid[x_pos][y_pos].id = air_id;
			new_frame_grid[x_pos - 1][y_pos + 1].id = sand_id;
		}
		else if (_downwardRight) {
			new_frame_grid[x_pos][y_pos].id = air_id;
			new_frame_grid[x_pos + 1][y_pos + 1].id = sand_id;
		}

	
}
void CellManager::update_water(int x_pos, int y_pos)
{
	new_frame_grid[x_pos][y_pos].occupied = true;


	bool _left = false, _right = false, _down = false, _downwardLeft = false, _downwardRight = false;

	if (old_frame_grid[x_pos][y_pos + 1].id == air_id) { // if air below - fall down 
		_down = true;
	}
	if (old_frame_grid[x_pos - 1][y_pos + 1].id == air_id) {
		_downwardLeft = true;
	}
	if (old_frame_grid[x_pos + 1][y_pos + 1].id == air_id) {
		_downwardRight = true;
	}
	if (old_frame_grid[x_pos - 1][y_pos].id == air_id) {
		_left = true;
	}
	if (old_frame_grid[x_pos + 1][y_pos].id == air_id) {
		_right = true;
	}
	
	if (_down) {
		new_frame_grid[x_pos][y_pos].id = air_id;
		new_frame_grid[x_pos][y_pos + 1].id = water_id;
	}
	else if (_downwardLeft) {
	
		new_frame_grid[x_pos][y_pos].id = air_id;
		new_frame_grid[x_pos - 1][y_pos + 1].id = water_id;
	}
	else if (_downwardRight) {
	
		new_frame_grid[x_pos][y_pos].id = air_id;
		new_frame_grid[x_pos + 1][y_pos + 1].id = water_id;
	}
	else if (_left && old_frame_grid[x_pos - 1][y_pos].occupied == false) {
		old_frame_grid[x_pos - 1][y_pos].occupied = true;
		new_frame_grid[x_pos][y_pos].id = air_id;
		new_frame_grid[x_pos - 1][y_pos].id = water_id;
	}
	else if (_right && old_frame_grid[x_pos + 1 ][y_pos].occupied == false) {
		old_frame_grid[x_pos + 1][y_pos].occupied = true;
		new_frame_grid[x_pos][y_pos].id = air_id;
		new_frame_grid[x_pos + 1][y_pos].id = water_id;
	}
	
	
	
	
	
	
	
	

}	








