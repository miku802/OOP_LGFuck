#pragma once

#ifndef STONE_H

#define STONE_H
#include "../Library//gameutil.h"
#include "config.h"

using namespace game_framework;

class Stone :public CMovingBitmap {
public:
	Stone() {};
	int get_x();
	int get_y();

	//method
	void init_stone(int x, int y);
	void set_xy(int x, int y);
	void show_stone();
	bool touch_stone(int x, int y);
	void reset();

private:
	CMovingBitmap stone	;
	int x, y;
	bool touched = false;

};

#endif // !FLAG_H
