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

/*************************
** Game.cpp内変数 **
*************************/
static int mImageHandle;		//画像ハンドル格納用
static int mImageBackground;	//画像ハンドル格納用
static int mImageHp;			//画像ハンドル格納用
static int mgameStatus;			//ゲームステータス変数

static int Seigen;				//時間制限用変数
static int mGameTime;			//ゲーム経過時間
static int StartTime;			//スタート用変数


/***********************************************
 * ゲーム　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Initialize()
{
	mImageBackground = LoadGraph("images/haikei3.png");	//画像のロード

	mImageHp = LoadGraph("images/select.png");			//画像のロード


	PlayMusic("sounds/kouhoBGM2.mp3", DX_PLAYTYPE_LOOP);//ゲーム中BGM再生


	Player_Initialize();
	Enemy_Initialize();

	StartTime = GetNowCount();	//経過した数値を入れる

	Seigen = 1;

	mGameTime = 0;

	mgameStatus = TRUE;
}


/***********************************************
 * ゲーム　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Finalize()
{
	DeleteGraph(mImageHandle);

	StopMusic();

	Player_Finalize();
	Enemy_Finalize();

}


/***********************************************
 * ゲーム　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Update()
{
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) //YボタンまたはESCキーで
	{
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}

	//ゲームプレイ中更新
	Player_Update();
	Enemy_Update();

	mGameTime++;

	Stage1();
}

/***********************************************
 * ゲーム　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Draw()
{

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

/***********************************************
 * ゲームオーバー処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void GameOver(void)
{
	const char* str2 = "---- Xキーを押してタイトルへ戻る ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2)				//xキーが押されていたら
	{
		SceneMgr_ChangeScene(eScene_Menu);	//メニュー画面に移行
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(140, 220, "ＧＡＭＥ ＯＶＥＲ", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}

/***********************************************
 * ゲームフィニッシュ処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void GameFinish()
{

	const char* str2 = "---- Xキーを押してタイトルへ戻る ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2)				//xキーが押されていたら
	{
		SceneMgr_ChangeScene(eScene_Menu);	//メニュー画面に移行
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(180, 220, "F I N I S H ! !", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}


/***********************************************
 * 時間制限
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void GameTime()
{
	Seigen = (30000 - (GetNowCount() - StartTime)) / 1000;

	if (Seigen > 0)
	{
		SetFontSize(25);
		DrawFormatString(250, 10, GetColor(255, 0, 0), "残り:%d秒", Seigen);
	}
	else
	{
		mgameStatus = false;

	}
}

/***********************************************
 * ゲーム時間取得
 * 引　数：なし
 * 戻り値：mGameTime
 ***********************************************/
int Game_GetmGameTime()
{
	return mGameTime;
}

/***********************************************
 * ゲーム状況セット
 * 引　数：flg
 * 戻り値：mGameTime
 ***********************************************/
void Game_SetmgameStatus(int flg)
{
	mgameStatus = flg;
}
