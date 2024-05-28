#pragma once

#ifndef FLAG_H

#define FLAG_H
#include "../Library//gameutil.h"
#include "config.h"

using namespace game_framework;

class Flag :public CMovingBitmap {
public:
	Flag() {};
	//setter
	int get_x() ;
	int get_y() ;
	bool get_touched();

	//method
	void init_flag(int x, int y);
	void set_xy(int x, int y);
	void show_flag();
	bool touch_flag(int x, int y);
	void regame();

private:
	CMovingBitmap flag;
	int x, y;
	bool touched = false;

};

#endif // !FLAG_H
