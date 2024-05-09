#include "stdafx.h"
#include "map.h"
#include <fstream>
#include <string>
//44*68(32*56

bool Map::const_turn() {
	if (abs(move_x) <= 3 && abs(move_y) <= 3)
		return true;
	return false;
}

bool Map::touch_wall(int now_derect) {
	if (now_derect == 0 && map_array[-x][-y - 1] == 1)
		return true;
	else if (now_derect == 3 && map_array[-x + 1][-y] == 1)
		return true;
	else if (now_derect == 6 && map_array[-x][-y + 1] == 1)
		return true;
	else if (now_derect == 9 && map_array[-x - 1][-y] == 1)
		return true;
	return false;
}

void Map::set_speed(int speed) {
	this->speed = speed;
}

void Map::init_map(int a, int b) {
	map.LoadBitmapByString({"Resources/map/map" + std::to_string(a) + "_" + std::to_string(b) + ".bmp"}); //+ "_" + std::to_string(b)
	this->x = 0 - 16;
	this->y = 0 - 50;
	map.SetTopLeft(this->x * a_unit, this->y * a_unit);
	Map::make_map(a, b);
}

void Map::show_map() {
	map.ShowBitmap(1);
}

void Map::move_map(int now_derect) {
	if (last_derect != now_derect) {
		last_derect = now_derect;
		return;
	}
	switch (now_derect)
	{
	case 0:
		if (map_array[-x][-y - 1] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_x = 0;
		move_y += speed;
		if (move_y >= a_unit)
		{
			y += 1;
			move_y = 0;
		}
		break;
	case 3:
		if (map_array[-x + 1][-y] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_y = 0;
		move_x -= speed;
		if (move_x <= -a_unit)
		{
			x -= 1;
			move_x = 0;
		}
		break;
	case 6:
		if (map_array[-x][-y + 1] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_x = 0;
		move_y -= speed;
		if (move_y <= -a_unit)
		{
			y -= 1;
			move_y = 0;
		}
		break;
	case 9:
		if (map_array[-x - 1][-y] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_y = 0;
		move_x += speed;
		if (move_x >= a_unit)
		{
			x += 1;
			move_x = 0;
		}
		break;

	default:
		break;
	}
	map.SetTopLeft(x * a_unit + move_x, y * a_unit + move_y);
	last_derect = now_derect;
}

void Map::make_map(int a, int b) {
	for (int i = 0; i < 65; i++)
		for (int j = 0; j < 40; j++)
			map_array[j][i] = -1;

	std::ifstream map("Resources/map/map" + std::to_string(a) + "_" + std::to_string(b) + ".txt");// + "_" + std::to_string(b) 
	for (int i = 0; i < 58; i++)
		for (int j = 0; j < 34; j++)
			map >> map_array[j][i];

	map.close();
}