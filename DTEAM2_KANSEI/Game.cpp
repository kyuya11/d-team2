#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "stage.h"
#include "Help.h"


static int mImageHandle;
static int mImageBackground;
static int mImageHp;
static int mgameStatus;

static int Seigen;
static int mGameTime;
static int StartTime;

static int mScroll1;
static int mScroll2;

void Game_Initialize() 
{
	mImageBackground = LoadGraph("images/haikei3.png");

	mImageHp = LoadGraph("images/select.png");


	PlayMusic("sounds/kouhoBGM2.mp3", DX_PLAYTYPE_LOOP);

	mScroll1 = 0;
	mScroll2 = 640;

	Player_Initialize();
	Enemy_Initialize();

	StartTime = GetNowCount();

	Seigen = 1;

	mGameTime = 0;

	mgameStatus = TRUE;
}

void Game_Finalize() 
{
	DeleteGraph(mImageHandle);

	StopMusic();

	Player_Finalize();
	Enemy_Finalize();

}

void Game_Update() 
{
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) 
	{
		SceneMgr_ChangeScene(eScene_Menu);//ƒV[ƒ“‚ðƒƒjƒ…[‚É•ÏX
	}

	Player_Update();
	Enemy_Update();

	mGameTime++;

	Stage1();
}

void Game_Draw() 
{

	DrawGraph(mScroll1, 0, mImageBackground, TRUE);

	if (mPlayer.hp > 0 && Seigen > 0) 
	{
		Player_Draw();
		Enemy_Draw();
		GameTime();
	}

	if (mPlayer.hp <= 0 && mgameStatus == TRUE) 
	{
		GameOver();
	}
	if (Seigen <= 0)
	{
		GameFinish();
	}
	else
	{
		SetFontSize(25);
		DrawString(475, 10, "HP:", 0x0000ff, 0);

		for (int i = 0; i < mPlayer.hp; i++) {
			DrawGraph(515 + i * 25, 5, mImageHp, TRUE);
		}
	}

}

void GameOver(void)
{
	const char* str2 = "---- XƒL[‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö–ß‚é ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2) 
	{
		SceneMgr_ChangeScene(eScene_Menu);
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(140, 220, "‚f‚`‚l‚d ‚n‚u‚d‚q", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}

void GameFinish()
{

	const char* str2 = "---- XƒL[‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö–ß‚é ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2)
	{
		SceneMgr_ChangeScene(eScene_Menu);
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(180, 220, "F I N I S H ! !", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}

void GameTime()
{
	Seigen = (30000 - (GetNowCount() - StartTime)) / 1000;

	if (Seigen > 0)
	{
		SetFontSize(25);
		DrawFormatString(250, 10, GetColor(255, 0, 0), "Žc‚è:%d•b", Seigen);
	}
	else
	{
		mgameStatus = false;

	}
}

int Game_GetmGameTime() 
{
	return mGameTime;
}

void Game_SetmgameStatus(int flg) 
{
	mgameStatus = flg;
}
