#include "stdafx.h"
#include "skill.h"
#include <fstream>
#include <string>

int Skill::get_x() {
	return x;
}

int Skill::get_y() {
	return y;
}

void Skill::init_skill() {
	skill.LoadBitmapByString({ "Resources/skill.bmp" });
	skill.SetTopLeft(-100, -100);
	show_time = 0;
}

void Skill::set_xy(int x, int y) {
	this->x = x;
	this->y = y;
	show_time++;
}

void Skill::set_position(int x, int y) {
	skill.SetTopLeft(x + 5 * a_unit + 4, y + 5 * a_unit);
}

int Skill::iru() {
	if (show_time >= 390 || show_time <= 0) {
		return 0;
	}
	return 1;
}

void Skill::show_skill(int map_x, int map_y) {
	if (show_time >= 400) {
		return;
	}
	
	skill.ShowBitmap(0.16);
	show_time++;
}

void Skill::reset() {
	show_time = 0;
}