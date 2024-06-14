#pragma once

#ifndef SKILL_H

#define SKILL_H
#include "../Library//gameutil.h"
#include "config.h"

using namespace game_framework;

class Skill :public CMovingBitmap {
public:
	Skill() {};
	int get_x();
	int get_y();
	int iru();

	//method
	void init_skill();
	void set_xy(int x, int y);
	void set_position(int x, int y);
	void show_skill(int map_x, int map_y);
	void reset();

private:
	CMovingBitmap skill;
	int x, y;
	int show_time;
	bool touched = false;

};

#endif // !FLAG_H
