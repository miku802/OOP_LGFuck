#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>
#include <fstream>  // 包含處理檔案的功能

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
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	turn_my_car();
	move_background();
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	my_car.LoadBitmapByString({								//我方車車
		"Resources/mycar1.bmp",
		"Resources/mycar2.bmp",
		"Resources/mycar3.bmp",
		"Resources/mycar4.bmp",
		"Resources/mycar5.bmp",
		"Resources/mycar6.bmp",
		"Resources/mycar7.bmp",
		"Resources/mycar8.bmp",
		"Resources/mycar9.bmp",
		"Resources/mycar10.bmp",
		"Resources/mycar11.bmp",
		"Resources/mycar12.bmp"
		});
	my_car.SetTopLeft(401, 157);

	background_road.LoadBitmapByString({"Resources/road.bmp"});
	background_road.SetTopLeft(background_location_now[0], background_location_now[1]);

	make_map();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		my_car_derect_goal = 0;
	}
	else if(nChar == VK_RIGHT)
	{
		my_car_derect_goal = 3;
	}
	else if (nChar == VK_DOWN)
	{
		my_car_derect_goal = 6;
	}
	else if (nChar == VK_LEFT)
	{
		my_car_derect_goal = 9;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
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
	background_road.ShowBitmap(8);
	my_car.ShowBitmap(0.095);
}

void CGameStateRun::turn_my_car()							//我方車車轉圈圈
{
	if (my_car_derect_now == 0 && my_car_derect_goal == 9)
	{
		my_car_derect_now = 11;
	}
	else if (my_car_derect_now < my_car_derect_goal || (my_car_derect_now >= 9 && my_car_derect_goal == 0))
	{
		my_car_derect_now++;
	}
	else if (my_car_derect_now > my_car_derect_goal)
	{
		my_car_derect_now--;
	}
	if (my_car_derect_now > 11)
	{
		my_car_derect_now = 0;
	}
	my_car.SetFrameIndexOfBitmap(my_car_derect_now);
	return;
}

void CGameStateRun::move_background()			//移動背景
{
	switch (my_car_derect_now)
	{
	case 0:
		if (map_test1[6 - (background_location_now[0] / 64 + 5)][6 - (background_location_now[1] / 64 + 2 )] == 1)
		{
			speed = 0;
			break;//left up     ( 0, 4) (-4, 4)
		}		  // right down ( 0, 0) (-4, 0)
		background_location_now[1] += speed;
		break;
	case 3:
		background_location_now[0] -= speed;
		break;
	case 6:
		background_location_now[1] -= speed;
		break;
	case 9:
		background_location_now[0] += speed;
		break;

	default:
		break;
	}
	background_road.SetTopLeft(background_location_now[0]+320, background_location_now[1]-85);
}

void CGameStateRun::make_map() 
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			map_test1[i][j] = 1;

	std::ifstream inputfile("Resources_map/map_test.txt");
	for (int i=0; i<7; i++)
		for (int j = 0; j < 7; j++)
			inputfile >> map_test1[i][j];
	return;
}