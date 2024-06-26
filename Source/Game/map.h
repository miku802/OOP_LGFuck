#pragma once

#ifndef	MAP_H

#define MAP_H
//#define normal_speed 10
#include "../Library/gameutil.h"
#include "config.h"
#include "flag.h"
#include "stone.h"
#include "skill.h"
#include "enemy_car.h"
#include <ddraw.h>
#include "../Library/gamecore.h"

using namespace game_framework;

class Map :public CMovingBitmap {
public:
	Map() {};
	int get_score();
	void set_score(int s);
	bool const_turn();
	bool touch_wall(int now_derect);
	void set_speed(int speed);
	void init_map(int a, int b);
	void show_map();
	void move_map(int now_derect, int oil);
	void make_map(int a);
	void make_enemy_car();
	void make_flags(int a, int b);
	void make_stone(int a, int b);
	bool show_bang();
	void reset();
	int get_flag_amount();
	void set_car_died(int a);
	int touch_enemy_car();
	void use_skill();
	void slow_down();

	//small map
	void init_small_map();

protected:
	int last_derect = 0;

private:
	CMovingBitmap map;
	CMovingBitmap right_black;
	CMovingBitmap bang;
	Flag flags[10];
	Stone stone[15];
	Enemy_car enemy_car[5];
	Skill skill[30];
	int stone_amount = 0;
	int bump = 0;
	int x, y;
	int last_x, last_y;
	int score = 0;
	int move_x = 0;
	int move_y = 0;
	int normal_speed;
	int speed = normal_speed;
	int map_array[40][65];
	int flag_amount = 10;
	int died = 0;
	int add_score_wait = 0;
	int saba;
	int add_score_tmp = 0;
	int skill_num;
	int last_iru[30];

	//small map
	CMovingBitmap small_map_background;
	CMovingBitmap small_my_car;
	CMovingBitmap small_enemy_car[5];
	CMovingBitmap small_flags[10];
};

#endif