#include "stdafx.h"
#include "stone.h"
#include <fstream>
#include <string>

int Stone::get_x() {
	return x;
}

int Stone::get_y() {
	return y;
}

void Stone::init_stone(int x, int y) {
	this->x = x;
	this->y = y;
	stone.LoadBitmapByString({ "Resources/stone.bmp" });
	stone.SetTopLeft(x * a_unit, y * a_unit);
}

void Stone::set_xy(int x, int y) {
	stone.SetTopLeft(x + 5 * a_unit + 4, y + 5 * a_unit);
}

void Stone::show_stone() {
	stone.ShowBitmap(0.16);
}

bool Stone::touch_stone(int x, int y) {
	if (x == this->x && y == this->y) {
		touched = true;
		return true;
	}
	return false;
}

void Stone::reset() {
	touched = false;
	stone.SetTopLeft(-100, -100);
}