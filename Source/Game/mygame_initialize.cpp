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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	background.LoadBitmapByString({ "Resources/yellow.bmp" });
	background.SetTopLeft(50, 0);


	//load_background();

	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

/*
void CGameStateInit::load_background()
{
	background.LoadBitmap({ "resources/falg.bmp", "resources/flag.bmp" });
	background.SetTopLeft(0, 0);
	background.SetAnimation(4000, true);
	background.ToggleAnimation();
}
*/

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap(2);
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 25, "Arial Black", RGB(255, 255, 255), 500);

	CTextDraw::Print(pDC, 750, -10, "HI-SCORE");
	CTextDraw::Print(pDC, 1025, 25, "20000");
	CTextDraw::Print(pDC, 750, 50, "1UP");
	CTextDraw::Print(pDC, 1045, 75, "0");

	CDDraw::ReleaseBackCDC();

}
