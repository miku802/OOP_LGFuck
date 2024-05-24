#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <fstream>
#include <memory>
#include <string>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{

}

void CGameStateRun::OnBeginState()
{
	//map->init_map(map_num, 1);
	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	switch (now_game_stage) {
	case MAP_CHOOSE:
		break;
	case MAP_PLAYING:
		map[map_num1]->move_map(my_car->get_now_derect());
		if (map[map_num1]->const_turn()) {
			if (map[map_num1]->touch_wall(my_car->get_goal_derect())) {
				my_car->set_goal_derect(my_car->get_now_derect());
			}
			else {
				my_car->turn_my_car();
			}
		}
		if (map[map_num1]->touch_wall(my_car->get_now_derect()) && my_car->get_goal_derect() == my_car->get_now_derect()) {
			if (!map[map_num1]->touch_wall(my_car->get_now_right())) {
				my_car->set_goal_derect(my_car->get_now_right());
			}
			else if (!map[map_num1]->touch_wall(my_car->get_now_left())) {
				my_car->set_goal_derect(my_car->get_now_left());
			}
			else {
				my_car->set_goal_derect(my_car->get_now_back());
			}
		}
		break;
	case MAP_WIN:
		break;
	case MAP_DIE:
		break;
	default:
		break;
	}
	oil->oil_decrease(1);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	my_car = std::make_shared<My_car>();
	my_car->init_my_car();
	//map->init_map(map_num, 1);
	choose_stage_gackground.LoadBitmapByString({ "Resources/game_init_pic/choose_stage_background.bmp" });
	choose_stage_gackground.SetTopLeft(0, 0);
	int x = 60, y = 240;
	for (int i = 0; i < 4; i++) {
		map[i] = std::make_shared<Map>();
		map[i]->init_map(i + 1);
		for (int j = 0; j < 4; j++) {
			choose_stage_map[i][j] = std::make_shared<CMovingBitmap>();
			choose_stage_map[i][j]->LoadBitmapByString({ "Resources/map/map" + std::to_string(i + 1) + ".bmp" });
			choose_stage_map[i][j]->SetTopLeft(x, y);
			x += 165;

		}
		if (i == 1) {
			x = 60;
			y = 630;
		}
	}

	right_black.LoadBitmapByString({ "Resources/black.bmp" });
	right_black.SetTopLeft(a_unit * 11 + 20, 0);

	oil = std::make_shared<Oil>();
	oil->oil_init();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x57) {		//w
		my_car->set_goal_derect(0); 
	}
	if (nChar == 0x53) {		//s
		my_car->set_goal_derect(6);
	}
	if (nChar == 0x41) {		//a
		my_car->set_goal_derect(9);
	}
	if (nChar == 0x44) {		//d
		my_car->set_goal_derect(3);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if ((WM_LBUTTONDOWN) && now_game_stage == MAP_CHOOSE) {
		mouse_x = point.x;
		mouse_y = point.y;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				switch (i)
				{
				case 0:
					if (mouse_x > 165 * j + 60 && mouse_x < 165 * j + 170 && mouse_y > 240 && mouse_y < 240 + 170) {
						map_num1 = 0;
						now_game_stage = MAP_PLAYING;
					}
					break;
				case 1:
					if (mouse_x > 165 * (j + 4) + 60 && mouse_x < 165 * (j + 4) + 170 && mouse_y > 240 && mouse_y < 240 + 170) {
						map_num1 = 1;
						now_game_stage = MAP_PLAYING;
					}
					break;
				case 2:
					if (mouse_x > 165 * j + 60 && mouse_x < 165 * j + 170 && mouse_y > 240 + 390 && mouse_y < 240 + 170 + 390) {
						map_num1 = 2;
						now_game_stage = MAP_PLAYING;
					}
					break;
				case 3:
					if (mouse_x > 165 * (j + 4) + 60 && mouse_x < 165 * (j + 4) + 170 && mouse_y > 240 + 390 && mouse_y < 240 + 170 + 390) {
						map_num1 = 3;
						now_game_stage = MAP_PLAYING;
					}
					break;
				default:
					break;
				}
			}
		}

	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	switch (now_game_stage)
	{
	case MAP_CHOOSE:
		choose_stage_gackground.ShowBitmap(1);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				choose_stage_map[i][j]->ShowBitmap(0.03125);
			}
		}
		break;
	case MAP_PLAYING:
		map[map_num1]->show_map();
		right_black.ShowBitmap(5);
		my_car->show_my_car();
		oil->show_oil();
		break;
	case MAP_WIN:
		break;
	case MAP_DIE:
		break;
	default:
		break;
	}
}
