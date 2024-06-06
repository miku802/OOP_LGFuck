#pragma once

#ifndef OIL_H

#define MAP_H
#include "../Library//gameutil.h"
#include "config.h"

using namespace game_framework;

class Oil :public CMovingBitmap {
public:
	Oil() {};
	void oil_init();
	void show_oil();
	void oil_decrease(int i);
	void reset();

private:
	CMovingBitmap oil_now[250];
	CMovingBitmap oil_ruler;
	int oil = 10000;
	
};

#endif // !OIL_H
