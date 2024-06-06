#pragma once

#ifndef MY_CAR_H

#define MY_CAR_H
#include "../Library/gameutil.h"
#include "config.h"

using namespace game_framework;

class My_car :public CMovingBitmap{
public:
	My_car() {};

	//getter
	int get_x();
	int get_y();
	int get_now_derect();
	int get_goal_derect();
	int get_now_right();
	int get_now_left();
	int get_now_back();

	//setter
	void set_xy(int x, int y);
	void set_goal_derect(int goal_derect);
	void set_now_derect(int now_derect);
	 
	//method
	void init_my_car();
	void show_my_car();
	void turn_my_car();
	void reset();

protected:
	bool turn_waiting();

private:

	CMovingBitmap my_car;
	int x, y;
	int goal_derect = 0;
	int now_derect = 0;
	int show_derect = 0;
	int show_const = 0;

};

#endif