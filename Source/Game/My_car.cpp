#include "stdafx.h"
#include "My_car.h"

int My_car::get_x() {
	return x;
}

int My_car::get_y() {
	return y;
}

int My_car::get_now_derect() {
	return now_derect;
}

int My_car::get_goal_derect() {
	return goal_derect;
}

int My_car::get_now_right() {
	if (now_derect == 9) {
		return 0;
	}
	return now_derect + 3;
}

int My_car::get_now_left() {
	if (now_derect == 0) {
		return 9;
	}
	return now_derect - 3;
}

int My_car::get_now_back() {
	if (now_derect <= 3) {
		return now_derect + 6;
	}
	return now_derect - 6;
}

void My_car::set_xy(int x, int y) {
	this->x = x;
	this->y = y;
	my_car.SetTopLeft(x, y);
}

void My_car::set_goal_derect(int goal_derect) {
	if (goal_derect < 0) {
		this->goal_derect = 9;
	}
	else if (goal_derect > 11) {
		this->goal_derect = 0;
	}
	else {	
		this->goal_derect = goal_derect;
	}
}

void My_car::init_my_car() {
	my_car.LoadBitmapByString({								//我方車車
		"Resources/My_car/mycar1.bmp",
		"Resources/My_car/mycar2.bmp",
		"Resources/My_car/mycar3.bmp",
		"Resources/My_car/mycar4.bmp",
		"Resources/My_car/mycar5.bmp",
		"Resources/My_car/mycar6.bmp",
		"Resources/My_car/mycar7.bmp",
		"Resources/My_car/mycar8.bmp",
		"Resources/My_car/mycar9.bmp",
		"Resources/My_car/mycar10.bmp",
		"Resources/My_car/mycar11.bmp",
		"Resources/My_car/mycar12.bmp"});
	My_car::set_xy(5 * a_unit + 8, 5 * a_unit + 8);
	my_car.SetTopLeft(x, y);
}

void My_car::show_my_car() {
	//My_car::turn_my_car();
	my_car.ShowBitmap(0.16);
	if (show_derect != now_derect && turn_waiting()) {
		if (show_derect == 0 && now_derect == 9)
		{
			show_derect = 11;
		}
		else if (show_derect < now_derect || (show_derect >= 9 && now_derect == 0))
		{
			show_derect++;
		}
		else if (show_derect > now_derect)
		{
			show_derect--;
		}
		if (show_derect > 11)
		{
			show_derect = 0;
		}
		else if (show_derect < 0)
		{
			show_derect = 11;
		}
	}
	if (show_derect < 0 || show_derect > 11) {
		return;
	}
	my_car.SetFrameIndexOfBitmap(show_derect);
}

void My_car::turn_my_car() {
	now_derect = goal_derect;

	//now_derect = goal_derect;
}

bool My_car::turn_waiting() {
	show_const++;
	if (show_const > 2) {
		show_const = 0;
		return true;
	}
	return false;
}