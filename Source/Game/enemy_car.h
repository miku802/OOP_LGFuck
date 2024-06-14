#pragma once

#ifndef	ENEMY_CAR_H

#include "../Library/gameutil.h"
#include "config.h"
#define enemy_speed 16

using namespace game_framework;

class Enemy_car :public CMovingBitmap {
public:
	Enemy_car() {};
	int get_x();
	int get_y();
	void set_goal_derect(int x);
	void init_enemy_car();
	void show_enemy_car();
	void turn_enemy_car(int x, int y);
	void set_position(int x, int y);
	void set_x(int x);
	void set_y(int y);
	void move_enemy_car(int my_x, int my_y, int front, int behind, int left, int right);
	bool turn_waiting();
	void bump();
	void reset();
	int stop;
	int saba;

private:
	CMovingBitmap enemy_car;
	int x, y;
	int move_x, move_y;
	int now_derect;
	int goal_derect;
	int speed;
	int show_const;
	int tmp;
};

#endif