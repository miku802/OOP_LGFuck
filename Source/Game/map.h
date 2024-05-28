#pragma once

#ifndef	MAP_H

#define MAP_H
#define normal_speed 10
#include "../Library/gameutil.h"
#include "config.h"

using namespace game_framework;

class Map :public CMovingBitmap {
public:
	Map() {};
	bool const_turn();
	bool touch_wall(int now_derect);
	void set_speed(int speed);
	void init_map(int a);
	void show_map();
	void move_map(int now_derect);
	void make_map(int a);

protected:
	int last_derect = 0;

private:
	CMovingBitmap map;
	int x, y;
	int move_x = 0;
	int move_y = 0;
	int speed = normal_speed;
	int map_array[40][65];
};

#endif