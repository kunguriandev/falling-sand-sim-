#pragma once
#include"SFML/Graphics.hpp"

struct Cell {
	int id;
	bool occupied;
};
class CellManager {

	static const int width = 133;
	static const int height = 133;

	Cell old_frame_grid[width][height];
	Cell new_frame_grid[width][height];

public:
	CellManager();
	void Update();
	void Draw(sf::RenderWindow& _window);
	void Clear();
	void CreateSand(int x_pos, int y_pos);
	void CreateStone(int x_pos, int y_pos);
	void CreateWater(int x_pos, int y_pos);
	void DeleteCell(int x_pos, int y_pos);
	int cell_size = 3;


private:
	void update_sand(int x_pos, int y_pos);
	void update_water(int x_pos, int y_pos);

	static const int air_id = 0;
	static const int sand_id = 1;
	static const int stone_id = 2;
	static const int water_id = 3;
};