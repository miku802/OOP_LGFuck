#include "stdafx.h"
#include "flag.h"
#include <fstream>
#include <string>

int Flag::get_x() {
	return x;
}

int Flag::get_y() {
	return y;
}

bool Flag::get_touched() {
	return touched;
}

void Flag::init_flag(int x, int y) {
	this->x = x;
	this->y = y;
	flag.LoadBitmapByString({ "Resources/flag.bmp" });
	flag.SetTopLeft(x * a_unit, y * a_unit);
}

void Flag::set_xy(int x, int y) {
	flag.SetTopLeft(x + 5 * a_unit, y + 5 * a_unit);
}

void Flag::show_flag() {
	if (touched) {
		return;
	}
	flag.ShowBitmap(0.16);
}

bool Flag::touch_flag(int x, int y) {
	if (touched == true)return false;
	if (x == this->x && y == this->y) {
		touched = true;
		return true;
	}
	return false;
}