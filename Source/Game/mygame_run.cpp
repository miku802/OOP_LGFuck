#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "config.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <fstream>  // 包含處理檔案的功能

using namespace game_framework;

#define normal_speed 20
#define path_map1 "map1"
//#define rock_x 20
//#define rock_y 49

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
	my_car.SetTopLeft((map_x + 7) * my_percent + 5, (map_y + 7) * my_percent + 7);

	background_road.LoadBitmapByString({"Resources/" + string(path_map1) + ".bmp"});	//背景
	background_road.SetTopLeft(background_location_now[0], background_location_now[1]);
	background_location_now[0] = (-16 + map_x);//-16
	background_location_now[1] = (-50 + map_y);//-50
	background_road.SetTopLeft(background_location_now[0] * my_percent, background_location_now[1] * my_percent);

	make_map();

	for (int i = 0; i < 10; i++)
	{
		do
		{
			std::random_device rd;  // 用來獲得隨機數種子
			std::mt19937 gen(rd()); // 以隨機數種子初始化Mersenne Twister產生器
			std::uniform_int_distribution<> distr(1, 100); // 定義一個從1到100的均勻分佈
			rock_x[i] = (distr(gen)) % 35;
			rock_y[i] = (distr(gen)) % 59;
		} while (map_array[rock_x[i]][rock_y[i]] == 1);
		rock[i].LoadBitmapByString({ "Resources/rock.bmp" });
		
	}
}

void CGameStateRun::OnShow()
{
	background_road.ShowBitmap(0.2 * 0.5 * my_percent);
	for (int i = 0; i < 10; i++)
	{
		rock[i].ShowBitmap(0.0022 * my_percent);
	}
	my_car.ShowBitmap(0.0018 * my_percent); // 0.0025
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE)
	{
		if (muda_bool == 0)
		{
			mudamudamudamuda();
			muda_bool = 1;
		}
		else if (muda_bool == 1)
		{
			make_map();
			muda_bool = 0;
		}
	}
	if (nChar == VK_UP)
	{
		if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y + 1))] == 1)return;
		my_car_derect_goal = 0;
	}
	else if(nChar == VK_RIGHT)
	{
		if (map_array[-int((background_location_now[0] - map_x - 1))][-int((background_location_now[1] - map_y))] == 1)return;
		my_car_derect_goal = 3;
	}
	else if (nChar == VK_DOWN)
	{
		if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y - 1))] == 1)return;
		my_car_derect_goal = 6;
	}
	else if (nChar == VK_LEFT)
	{
		if (map_array[-int((background_location_now[0] - map_x + 1))][-int((background_location_now[1] - map_y))] == 1)return;
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
	if (my_car_derect_now == my_car_derect_goal)speed = 20;
	my_car.SetFrameIndexOfBitmap(my_car_derect_now);
	return;
}

int CGameStateRun::touch_rock()
{
	for (int i = 0; i < 10; i++)
	{
		if (-(background_location_now[0]) == rock_x[i] && (-(background_location_now[1])) == rock_y[i])
			return 1;
	}
	return 0;
}

void CGameStateRun::move_background()			//移動背景
{
	if (my_car_derect_now != my_car_derect_goal)return;
	else if (touch_rock())
	{
		speed = 0;
		my_car_derect_goal += 3;
		if (my_car_derect_goal == 12) { my_car_derect_goal = 0; }
		turn_my_car();
	}
	else speed = normal_speed;
	switch (my_car_derect_now)
	{
	case 0:
		if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y + 1))] == 1)
		{
			my_car_derect_goal = 3;
			if (map_array[-int((background_location_now[0] - map_x - 1))][-int((background_location_now[1] - map_y))] == 1)
				my_car_derect_goal = 9;
			return;
		}
		move[1] = 0;
		move[0] += speed;
		if (move[0] >= 100) 
		{
			background_location_now[1] += 1;
			move[0] = 0;
		}
		break;
	case 3:
		if (map_array[-int((background_location_now[0] - map_x - 1))][-int((background_location_now[1] - map_y))] == 1)
		{
			my_car_derect_goal = 6;
			if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y - 1))] == 1)
				my_car_derect_goal = 0;
			return;
		}
		move[0] = 0;
		move[1] -= speed;
		if (move[1] <= -100)
		{
			background_location_now[0] -= 1;
			move[1] = 0;
		}
		break;
	case 6:
		if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y - 1))] == 1)
		{
			my_car_derect_goal = 9;
			if (map_array[-int((background_location_now[0] - map_x + 1))][-int((background_location_now[1] - map_y))] == 1)
				my_car_derect_goal = 3;
			return;
		}
		move[1] = 0;
		move[0] -= speed;
		if (move[0] <= -100)
		{
			background_location_now[1] -= 1;
			move[0] = 0;
		}
		break;
	case 9:
		if (map_array[-int((background_location_now[0] - map_x + 1))][-int((background_location_now[1] - map_y))] == 1)
		{
			my_car_derect_goal = 0;
			if (map_array[-int((background_location_now[0] - map_x))][-int((background_location_now[1] - map_y + 1))] == 1)
				my_car_derect_goal = 6;
			return;
		}
		move[0] = 0;
		move[1] += speed;
		if (move[1] >= 100)
		{
			background_location_now[0] += 1;
			move[1] = 0;
		}
		break;

	default:
		break;
	}
	background_road.SetTopLeft((background_location_now[0]) * my_percent + move[1]/2, (background_location_now[1])* my_percent + move[0]/2);
	for (int i = 0; i < 10; i++)
	{
		rock[i].SetTopLeft((background_location_now[0] + rock_x[i] + 7) * my_percent + move[1] / 2 + 3, (background_location_now[1] + rock_y[i] + 7)* my_percent + move[0] / 2 + 3);
	}
}

void CGameStateRun::make_map()
{
	for (int i = 0; i < 65; i++)
		for (int j = 0; j < 40; j++)
			map_array[j][i] = 1;

	std::ifstream inputfile("Resources_map/" + string(path_map1) + ".txt");
	for (int i = 0; i < 58; i++)
		for (int j = 0; j < 34; j++)
			inputfile >> map_array[j][i];
	return;
}

void CGameStateRun::mudamudamudamuda() // now 30*50
{
	for (int i = 0; i < 58; i++)
		for (int j = 0; j < 34; j++)
			if(i==0 || i==57 || j==0 || j==33)
				map_array[j][i] = 1;
			else
				map_array[j][i] = 0;
	return;
}