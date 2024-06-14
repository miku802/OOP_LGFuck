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
		map->move_map(my_car->get_now_derect(), oil->get_oil());
		if (map->const_turn()) {
			if (map->touch_wall(my_car->get_goal_derect())) {
				my_car->set_goal_derect(my_car->get_now_derect());
			}
			else {
				my_car->turn_my_car();
			}
		}
		if (map->touch_wall(my_car->get_now_derect()) && my_car->get_goal_derect() == my_car->get_now_derect()) {
			if (!map->touch_wall(my_car->get_now_right())) {
				my_car->set_goal_derect(my_car->get_now_right());
			}
			else if (!map->touch_wall(my_car->get_now_left())) {
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

	map = std::make_shared<Map>();

	int x = 60, y = 240;
	for (int i = 0; i < 4; i++) {
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

	for (int i = 0; i < 4; i++) {
		life_pic[i].LoadBitmapByString({ "Resources/life.bmp" });
		life_pic[i].SetTopLeft(930 + i * 80, 800);
	}

	oil = std::make_shared<Oil>();
	oil->oil_init();

	black = std::make_shared<CMovingBitmap>();
	black->LoadBitmapByString({ "Resources/black.bmp" });
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
	if (nChar == 0x46) {		//d
		map->use_skill();
		oil->decrease();
	}
	if (nChar == 0x50) {		//p
		skip = true;
	}
	if (nChar == 0x52) {		//r
		reset();
		map_num1 = 1, map_num2 = 0;
		map_win_wait = 0;
		skip = false;
		life = 4;
		map->set_score(0);
		now_game_stage = MAP_CHOOSE;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if ((WM_LBUTTONDOWN) && now_game_stage == MAP_DIE) {
		reset();
		now_game_stage = MAP_CHOOSE;	
	}
	//if ((WM_LBUTTONDOWN) && now_game_stage == MAP_CHOOSE) {
	//	mouse_x = point.x;
	//	mouse_y = point.y;

	//	for (int i = 0; i < 4; i++) {
	//		for (int j = 0; j < 4; j++) {
	//			switch (i)
	//			{
	//			case 0:
	//				if (mouse_x > 165 * j + 60 && mouse_x < 165 * j + 170 && mouse_y > 240 && mouse_y < 240 + 170) {
	//					map_num1 = 1;
	//					map_num2 = j + 1;
	//				}
	//				break;
	//			case 1:
	//				if (mouse_x > 165 * (j + 4) + 60 && mouse_x < 165 * (j + 4) + 170 && mouse_y > 240 && mouse_y < 240 + 170) {
	//					map_num1 = 2;
	//					map_num2 = j + 1;
	//				}
	//				break;
	//			case 2:
	//				if (mouse_x > 165 * j + 60 && mouse_x < 165 * j + 170 && mouse_y > 240 + 390 && mouse_y < 240 + 170 + 390) {
	//					map_num1 = 3;
	//					map_num2 = j + 1;
	//				}
	//				break;
	//			case 3:
	//				if (mouse_x > 165 * (j + 4) + 60 && mouse_x < 165 * (j + 4) + 170 && mouse_y > 240 + 390 && mouse_y < 240 + 170 + 390) {
	//					map_num1 = 4;
	//					map_num2 = j + 1;
	//				}
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	if (map_num1 != -1) {
	//		map->init_map(map_num1, map_num2);
	//		now_game_stage = MAP_PLAYING;
	//	}
	//}
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
		//
		if (map_num2 == 4 && map_num1 == 4) {
			now_game_stage = MAP_WIN;
			return;
		}
		map_num2++;
		if (map_num2 > 4) {
			map_num2 = 1;
			map_num1++;
		}
		map->init_map(map_num1, map_num2);
		now_game_stage = MAP_PLAYING;
		//
		//choose_stage_gackground.ShowBitmap(1);
		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		choose_stage_map[i][j]->ShowBitmap(0.03125);
		//	}
		//}
		break;
	case MAP_PLAYING:
		map->show_map();
		oil->show_oil();
		my_car->show_my_car();
		if (oil->get_oil() <= 1) {
			map->slow_down();
		}
		if (map->show_bang()) {
			my_car->reset();
			map_num2--;
			oil->reset();
			life--;
			map->set_car_died(1);
			now_game_stage = MAP_CHOOSE;
			if (life == 0) {
				now_game_stage = MAP_DIE;
			}
		}
		if (map->get_flag_amount() == 0 || skip == true) {
			skip = false;
			map_win_wait = 0;
			reset();
			black->ShowBitmap(10);
			now_game_stage = MAP_CHOOSE;
		}
		for (int i = 0; i < 4; i++) {
			if (i > life-1 || now_game_stage == MAP_CHOOSE) {
				break;
			}
			life_pic[i].ShowBitmap(0.8);
		}
		break;
	case MAP_WIN:
		//map_win_wait++;
		//if (map_win_wait > 100) {
		//	map_win_wait = 0;
		//	reset();
		//	now_game_stage = MAP_CHOOSE;
		//}
		break;
	case MAP_DIE:
		break;
	default:
		break;
	}
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 25, "Arial Black", RGB(255, 255, 255), 500);
	if (now_game_stage == MAP_PLAYING) {
		CTextDraw::Print(pDC, 930, 10, "STAGE：");
		CTextDraw::Print(pDC, 1100, 10, std::to_string(map_num1) + "-" + std::to_string(map_num2));
		CTextDraw::Print(pDC, 930, 60, "GOAL：");
		CTextDraw::Print(pDC, 1100, 60, "160000");
		CTextDraw::Print(pDC, 930, 110, "SCORE：");
		CTextDraw::Print(pDC, 1100, 110, std::to_string(map->get_score()));
	}
	if (now_game_stage == MAP_WIN) {
		CTextDraw::ChangeFontLog(pDC, 100, "Arial Black", RGB(255, 255, 255), 500);
		CTextDraw::Print(pDC, 500, 350, "WIN!!!");
		CTextDraw::ChangeFontLog(pDC, 30, "Arial Black", RGB(255, 255, 255), 500);
		CTextDraw::Print(pDC, 530, 850, "press r replay");
	}
	if (now_game_stage == MAP_DIE) {
		CTextDraw::ChangeFontLog(pDC, 100, "Arial Black", RGB(255, 255, 255), 500);
		CTextDraw::Print(pDC, 600, 350, "呵");
		CTextDraw::ChangeFontLog(pDC, 20, "Arial Black", RGB(255, 255, 255), 500);
		CTextDraw::Print(pDC, 535, 820, "press r replay");
	}
	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::reset() {
	my_car->reset();
	map->reset();
	oil->reset();
	//map_num1 = -1;
	//map_num2 = -1;
}