#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	Turn_my_car();
	move_background();
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	My_car.LoadBitmapByString({								//我方車車
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
	My_car.SetTopLeft(400, 250);

	Background_road.LoadBitmapByString({"Resources/road.bmp"});
	Background_road.SetTopLeft(-200, -100);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		My_car_goal_derect = 0;
	}
	else if(nChar == VK_RIGHT)
	{
		My_car_goal_derect = 3;
	}
	else if (nChar == VK_DOWN)
	{
		My_car_goal_derect = 6;
	}
	else if (nChar == VK_LEFT)
	{
		My_car_goal_derect = 9;
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
	Background_road.ShowBitmap(6);
	My_car.ShowBitmap(0.1);
}

void CGameStateRun::Turn_my_car()							//我方車車轉圈圈
{
	if (My_car_now_derect == 0 && My_car_goal_derect == 9)
	{
		My_car_now_derect = 11;
	}
	else if (My_car_now_derect < My_car_goal_derect || (My_car_now_derect >= 9 && My_car_goal_derect == 0))
	{
		My_car_now_derect++;
	}
	else if (My_car_now_derect > My_car_goal_derect)
	{
		My_car_now_derect--;
	}
	if (My_car_now_derect > 11) 
	{
		My_car_now_derect = 0;
	}
	My_car.SetFrameIndexOfBitmap(My_car_now_derect);
	return;
}

void CGameStateRun::move_background()
{
	switch (My_car_now_derect)
	{
	case 0:
		Background_road_now[1] += speed;
		break;
	case 3:
		Background_road_now[0] -= speed;
		break;
	case 6:
		Background_road_now[1] -= speed;
		break;
	case 9:
		Background_road_now[0] += speed;
		break;
	default:
		break;
	}
	Background_road.SetTopLeft(Background_road_now[0], Background_road_now[1]);
}