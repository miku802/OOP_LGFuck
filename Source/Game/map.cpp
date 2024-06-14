#include "stdafx.h"
#include "map.h"
#include <fstream>
#include <string>
//44*68(32*56

int Map::get_score() {
	return score;
}

void Map::set_score(int s) {
	score = s;
}

bool Map::const_turn() {
	if (abs(move_x) <= 3 && abs(move_y) <= 3)
		return true;
	return false;
}

bool Map::touch_wall(int now_derect) {
	if (now_derect == 0 && map_array[-x][-y - 1] == 1)
		return true;
	else if (now_derect == 3 && map_array[-x + 1][-y] == 1)
		return true;
	else if (now_derect == 6 && map_array[-x][-y + 1] == 1)
		return true;
	else if (now_derect == 9 && map_array[-x - 1][-y] == 1)
		return true;
	return false;
}

void Map::set_speed(int speed) {
	this->speed = speed;
}

void Map::slow_down() {
	if (speed == 4) {
		return;
	}
	saba++;
	if (saba >= 30) {
		normal_speed--;
		saba = 0;
	}
}

void Map::init_map(int a, int b) {
	saba = 0;
	bang.LoadBitmapByString({ "Resources/bang.bmp" });
	bang.SetTopLeft(5 * a_unit + 4, 5 * a_unit + 4);
	map.LoadBitmapByString({ "Resources/map/map1.bmp" ,"Resources/map/map2.bmp" ,"Resources/map/map3.bmp" ,"Resources/map/map4.bmp" }); //+ "_" + std::to_string(b)
	map.SetFrameIndexOfBitmap(a - 1);
	this->x = 0 - 16;
	this->y = 0 - 50;
	map.SetTopLeft(this->x * a_unit, this->y * a_unit);
	skill_num = 0;
	for (int i = 0; i < 30; i++) {
		skill[i].init_skill();
		last_iru[i] = 0;
	}
	normal_speed = 16;

	right_black.LoadBitmapByString({ "Resources/black.bmp" });
	right_black.SetTopLeft(a_unit * 11 + 20, 0);

	Map::make_map(a);
	Map::make_enemy_car();
	Map::make_flags(a, b);
	Map::make_stone(a, b);
	Map::init_small_map();
	for (int i = 0; i < 5; i++) {
		enemy_car[i].init_enemy_car();
		enemy_car[i].set_x(12 + 2 * i);
		enemy_car[i].set_y(52);
	}
}

void Map::make_map(int a) {
	for (int i = 0; i < 65; i++)
		for (int j = 0; j < 40; j++)
			map_array[j][i] = -1;

	std::ifstream map("Resources/map/map" + std::to_string(a) + ".txt");// + "_" + std::to_string(b) 
	for (int i = 0; i < 58; i++)
		for (int j = 0; j < 34; j++)
			map >> map_array[j][i];

	map.close();
}

void Map::make_enemy_car() {
	for (int i = 0; i < 5; i++) {
		enemy_car[i].set_x(12+2 * i);
		enemy_car[i].set_y(52);
	}
}

void Map::make_flags(int a, int b) {
	int x, y;
	std::ifstream flag_position("Resources/map/object/flag" + std::to_string(a) + std::to_string(b) + ".txt");// + "_" + std::to_string(b) 
	for (int i = 0; i < 10; i++) {
		flag_position >> x;
		flag_position >> y;
		flags[i].init_flag(x, y);
	}
	flag_position.close();
}

void Map::make_stone(int a, int b) {
	int x, y;
	std::ifstream stone_position("Resources/map/object/stone" + std::to_string(a) + std::to_string(b) + ".txt");// + "_" + std::to_string(b) 
	stone_position >> stone_amount;
	for (int i = 0; i < stone_amount; i++) {
		stone_position >> x;
		stone_position >> y;
		stone[i].init_stone(x, y);
	}
	stone_position.close();
}

void Map::init_small_map() {
	small_map_background.LoadBitmapByString({ "Resources/small map.bmp" });
	small_map_background.SetTopLeft(925, 300);

	small_my_car.LoadBitmapByString({ "Resources/small car 1.bmp" , "Resources/small car 2.bmp" });
	small_my_car.SetAnimation(200, false);
	small_my_car.SetTopLeft(925 - x*8, 748 + y*8);//x * a_unit + move_x, y * a_unit + move_y

	for (int i = 0; i < 5; i++) {
		small_enemy_car[i].LoadBitmapByString({ "Resources/small enemy.bmp" });
		small_enemy_car[i].SetTopLeft(925 - enemy_car[i].get_x() * 8, 748 + enemy_car[i].get_y() * 8);
	}

	for (int i = 0; i < 10; i++) {
		small_flags[i].LoadBitmapByString({ "Resources/small flag.bmp" });
		small_flags[i].SetTopLeft(925 + flags[i].get_x() * 8, 300 + flags[i].get_y() * 8);
	}
}

void Map::show_map() {
	map.ShowBitmap(1);
	for (int i = 0; i < 10; i++) {
		flags[i].show_flag();
	}
	for (int i = 0; i < stone_amount; i++) {
		stone[i].show_stone();
	}
	for (int i = 0; i < skill_num; i++) {
		skill[i].show_skill(-x, -y);
	}
	for (int i = 0; i < 5; i++) {
		enemy_car[i].set_position(
			x *	a_unit + move_x,
			y * a_unit + move_y);
		enemy_car[i].show_enemy_car();
	}
	right_black.ShowBitmap(5);
	small_map_background.ShowBitmap(0.8);
	small_my_car.ShowBitmap(0.8);
	for (int i = 0; i < 5; i++) {
		small_enemy_car[i].ShowBitmap(0.8);
	}
	for (int i = 0; i < 10; i++) {
		if (!flags[i].get_touched()) {
			small_flags[i].ShowBitmap(0.8);
		}
	}
	if (add_score_wait > 0) {
		add_score_wait++;

		CDC *pDC = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(pDC, 20, "Arial Black", RGB(255, 255, 255), 500);
		CTextDraw::Print(pDC, 1100, 90, "+" + std::to_string(add_score_tmp));
		if (add_score_wait > 30) {
			add_score_wait = 0;
		}
		CDDraw::ReleaseBackCDC();
	}
}

void Map::set_car_died(int a) {
	died = a;
}

void Map::move_map(int now_derect, int oil) {
	if (bump > 0) {
		return;
	}
	if (last_derect != now_derect) {
		last_derect = now_derect;
		return;
	}
	switch (now_derect)
	{
	case 0:
		if (map_array[-x][-y - 1] == 1)
		{
			speed = 0;
		}

		else speed = normal_speed;
		move_x = 0;
		move_y += speed;
		if (move_y >= a_unit)
		{
			y += 1;
			move_y = 0;
		}
		break;
	case 3:
		if (map_array[-x + 1][-y] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_y = 0;
		move_x -= speed;
		if (move_x <= -a_unit)
		{
			x -= 1;
			move_x = 0;
		}
		break;
	case 6:
		if (map_array[-x][-y + 1] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_x = 0;
		move_y -= speed;
		if (move_y <= -a_unit)
		{
			y -= 1;
			move_y = 0;
		}
		break;
	case 9:
		if (map_array[-x - 1][-y] == 1)
		{
			speed = 0;
		}
		else speed = normal_speed;
		move_y = 0;
		move_x += speed;
		if (move_x >= a_unit)
		{
			x += 1;
			move_x = 0;
		}
		break;

	default:
		break;
	}
	map.SetTopLeft(x * a_unit + move_x, y * a_unit + move_y);
	small_my_car.SetTopLeft(925 - x * 8, 300 - y * 8);
	for (int i = 0; i < 10; i++) {
		flags[i].set_xy((x + flags[i].get_x()) * a_unit + move_x, (y + flags[i].get_y()) * a_unit + move_y);
		if (flags[i].touch_flag(-x, -y)) {
			add_score_tmp = (11 - flag_amount)*(2 - died) * 100;
			score += (11 - flag_amount)*(2 - died) * 100;
			add_score_wait = 1;
			flag_amount--;
		}
		//flags[i].set_xy(x * a_unit + move_x, y * a_unit + move_y);
	}
	for (int i = 0; i < stone_amount; i++) {
		stone[i].set_xy((x + stone[i].get_x()) * a_unit + move_x, (y + stone[i].get_y()) * a_unit + move_y);
		if (stone[i].touch_stone(-x, -y)) {
			bump++;
		}
	}
	for (int i = 0; i < skill_num; i++) {
		skill[i].set_position((x + skill[i].get_x()) * a_unit + move_x, (y + skill[i].get_y()) * a_unit + move_y);
		if (skill[i].iru() == 1) {
			for (int j = 0; j < 5; j++) {
				if (skill[i].get_x() == enemy_car[j].get_x() && skill[i].get_y() == enemy_car[j].get_y()) {
					enemy_car[j].bump();
				}
			}
		}
		if (skill[i].iru() == 0 && last_iru[i] == 1) {
			for (int j = 0; j < 5; j++) {
				enemy_car[i].stop = 0;
			}
		}
		last_iru[i] = skill[i].iru();
	}

	last_derect = now_derect;
	for (int i = 0; i < 5; i++) {
		if (enemy_car[i].get_x() == 32) {
			enemy_car[i].get_x();
		}
	}
	if (touch_enemy_car() == 1) {
		bump++;
	}
	if(oil < 9800){
		for (int i = 0; i < 5; i++) {
			enemy_car[i].move_enemy_car(
				-x, -y,
				map_array[enemy_car[i].get_x()][enemy_car[i].get_y() - 1],
				map_array[enemy_car[i].get_x()][enemy_car[i].get_y() + 1],
				map_array[enemy_car[i].get_x() - 1][enemy_car[i].get_y()],
				map_array[enemy_car[i].get_x() + 1][enemy_car[i].get_y()]);
		}
	}
	for (int i = 0; i < 5; i++) {
		small_enemy_car[i].SetTopLeft(925 + enemy_car[i].get_x() * 8, 300 + enemy_car[i].get_y() * 8);
	}
		
}

int Map::touch_enemy_car() {
	for (int i = 0; i < 5; i++) {
		if (move_x > 0) {
			if ((enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y)
				//	||(enemy_car[i].get_x() ==-x + 1 && enemy_car[i].get_y() == -y) 
				) {
				return 1;
			}
		}
		if (move_x < -0) {
			if ((enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y)
				//	||(enemy_car[i].get_x() == -x - 1 && enemy_car[i].get_y() == -y)
				) {
				return 1;
			}
		}
		if (move_y > 0) {
			if ((enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y)
				//||(enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y - 1)
				) {
				return 1;
			}
		}
		if (move_x > 0) {
			if ((enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y)
				//||(enemy_car[i].get_x() == -x && enemy_car[i].get_y() == -y + 1)
				) {
				return 1;
			}
		}
	}
	return 0;
}

bool Map::show_bang() {
	if (bump > 0) {
		bump++;
		bang.ShowBitmap(0.16);
		if (bump > 100) {
			bump = 0;
			return true;
		}
	}
	return false;
}

void Map::reset() {
	saba = 0;
	move_x = 0;
	move_y = 0;
	flag_amount = 10;
	normal_speed = 16;
	skill_num = 0;
	speed = normal_speed;
	for (int i = 0; i < 10; i++) {
		flags[i].reset();
	}
	for (int i = 0; i < stone_amount; i++) {
		stone[i].reset();
	}
	for (int i = 0; i < 5; i++) {
		enemy_car[i].reset();
		enemy_car[i].set_x(12 + 2 * i);
		enemy_car[i].set_y(52);
	}
}

int Map::get_flag_amount() {
	return flag_amount;
}

void Map::use_skill() {
	skill[skill_num].set_xy(-x, -y);
	if (skill_num == 29)return;
	skill_num++;
	
}