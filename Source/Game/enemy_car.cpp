#include "stdafx.h"
#include "enemy_car.h"
#include <fstream>
#include <string>
#include <random>
//44*68(32*56

int Enemy_car::get_x() {
	return x;
}

int Enemy_car::get_y() {
	return y;
}

void Enemy_car::reset() {
	x = 16;
	y = 52;
	move_x = 0;
	move_y = 0;
	saba = 0;
	stop = 0;
	now_derect = 0;
	goal_derect = 0;
	speed = enemy_speed;
	show_const = 0;
}

void Enemy_car::init_enemy_car() {
	x = 16;
	y = 52;
	move_x = 0;
	move_y = 0;
	saba = 0;
	stop = 0;
	now_derect = 0;
	goal_derect = 0;
	speed = enemy_speed;
	show_const = 0;
	enemy_car.LoadBitmapByString({								//我方車車
		"Resources/redcar1.bmp",
		"Resources/redcar2.bmp",
		"Resources/redcar3.bmp",
		"Resources/redcar4.bmp",
		"Resources/redcar5.bmp",
		"Resources/redcar6.bmp",
		"Resources/redcar7.bmp",
		"Resources/redcar8.bmp",
		"Resources/redcar9.bmp",
		"Resources/redcar10.bmp",
		"Resources/redcar11.bmp",
		"Resources/redcar12.bmp" });
	enemy_car.SetTopLeft(-100, -100);
}

void Enemy_car::set_position(int map_x, int map_y) {
	enemy_car.SetTopLeft((x + 5)*a_unit - move_x  + map_x, (y + 5)*a_unit - move_y + map_y);
}

void Enemy_car::bump() {
	now_derect++;
	saba++;
	if (now_derect >= 12) {
		now_derect = 0;
	}
	stop = 1;
	enemy_car.SetFrameIndexOfBitmap(now_derect);
}

void Enemy_car::set_x(int x) {
	this->x = x;
}

void Enemy_car::set_y(int y) {
	this->y = y;
}

void Enemy_car::set_goal_derect(int x) {
	goal_derect = x;
}

int random_num() {
	static std::random_device rd;

	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(0, 1000);

	return dis(gen);
}

void Enemy_car::move_enemy_car(int my_x, int my_y, int front, int behind, int left, int right) {
	if (stop == 1) {
		return;
	}
	switch (goal_derect)
	{
	case 0:
		if (front == 1)
		{
			speed = 0;
			do {
				tmp = random_num() % 4;
			} while (tmp == 0);
			goal_derect = 3 * tmp;
			//if (right == 0) {
			//	goal_derect = 3;
			//}
			//else if (left == 0) {
			//	goal_derect = 9;
			//}
			//else {
			//	goal_derect = 6;
			//}
		}
		else speed = enemy_speed;
		move_x = 0;
		move_y += speed;
		if (move_y >= a_unit)
		{
			y -= 1;
			move_y = 0;
		}
		break;
	case 3:
		if (right == 1)
		{
			speed = 0;
			do {
				tmp = random_num() % 4;
			} while (tmp == 3);
			goal_derect = 3 * tmp;
			//if (behind == 0) {
			//	goal_derect = 6;
			//}
			//else if (front == 0) {
			//	goal_derect = 0;
			//}
			//else {
			//	goal_derect = 9;
			//}
		}
		else speed = enemy_speed;
		move_y = 0;
		move_x -= speed;
		if (move_x <= -a_unit)
		{
			x += 1;
			move_x = 0;
		}
		break;
	case 6:
		if (behind == 1)
		{
			speed = 0;
			do {
				tmp = random_num() % 4;
			} while (tmp == 6);
			goal_derect = 3 * tmp;
			//if (left == 0) {
			//	goal_derect = 9;
			//}
			//else if (right == 0) {
			//	goal_derect = 3;
			//}
			//else {
			//	goal_derect = 0;
			//}
		}
		else speed = enemy_speed;
		move_x = 0;
		move_y -= speed;
		if (move_y <= -a_unit)
		{
			y += 1;
			move_y = 0;
		}
		break;
	case 9:
		if (left == 1)
		{
			speed = 0;
			do {
				tmp = random_num()%4;
			} while (tmp == 9);
			goal_derect = 3 * tmp;
			//if (front == 0) {
			//	goal_derect = 0;
			//}
			//else if (behind == 0) {
			//	goal_derect = 6;
			//}
			//else {
			//	goal_derect = 3;
			//}
		}
		else speed = enemy_speed;
		move_y = 0;
		move_x += speed;
		if (move_x >= a_unit)
		{
			x -= 1;
			move_x = 0;
		}
		break;

	default:
		break;
	}
}

void Enemy_car::show_enemy_car() {
	enemy_car.ShowBitmap(0.16);
	if (now_derect != goal_derect && turn_waiting()) {
		if (now_derect == 0 && goal_derect == 9)
		{
			now_derect = 11;
		}
		else if (now_derect < goal_derect || (now_derect >= 9 && goal_derect == 0))
		{
			now_derect++;
		}
		else if (now_derect > goal_derect)
		{
			now_derect--;
		}
		if (now_derect > 11)
		{
			now_derect = 0;
		}
		else if (now_derect < 0)
		{
			now_derect = 11;
		}
	}
	if (now_derect < 0 || now_derect > 11) {
		return;
	}
	enemy_car.SetFrameIndexOfBitmap(now_derect);
}

bool Enemy_car::turn_waiting() {
	show_const++;
	if (show_const > 2) {
		show_const = 0;
		return true;
	}
	return false;
}

void Enemy_car::turn_enemy_car(int x, int y) {
	if (move_x != 0 || move_y != 0) {
		return;
	}
	if (this->y > y) {
		goal_derect = 0;
	}
	else if (this->y < y) {
		goal_derect = 6;
	}
	else if (this->x < x) {
		goal_derect = 3;
	}
	else if (this->x > x) {
		goal_derect = 9;
	}
}