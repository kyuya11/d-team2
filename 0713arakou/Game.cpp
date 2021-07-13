#include <string.h>
#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Game.h"
#include "Player.h"
//#include "Enemy.h"
//#include "stage.h"
//#include "Effect.h"
//#include "Help.h"
//#include "ITEM.h"

static int mImageHandle;
static int mImageBackground;
static int mImageHp;
static int mgameStatus;

static int mGameTime;

static int mScroll1;
static int mScroll2;

void Game_Initialize() 
{
	mImageBackground = LoadGraph("images/haikei3.png");

	mImageHp = LoadGraph("images/select.png");


	//PlayMusic("sounds/Stage.mp3", DX_PLAYTYPE_LOOP);

	mScroll1 = 0;
	mScroll2 = 640;

	Player_Initialize();
	//Enemy_Initialize();
	//Effect_Initialize();
	//Item_Initialize();


	mGameTime = 0;

	mgameStatus = TRUE;
}

void Game_Finalize() {
	DeleteGraph(mImageHandle);

	StopMusic();

	Player_Finalize();
	//Enemy_Finalize();
	//Effect_Finalize();
	//Item_Finalize();


}

void Game_Update() {
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}

	Player_Update();
	//Enemy_Update();
	//Effect_Update();
	//Item_Update();


	mGameTime++;

	//Stage1();
}

void Game_Draw() {

	BackScroll();

	Player_Draw();
	//Effect_Draw();
	//Item_Draw();
	//Enemy_Draw();

	//if (mEnemy->bosu == 1) {
	//	GameClear();
	//}
	//else if (mPlayer.hp <= 0 || mgameStatus == FALSE) {
	//	GameOver();
	//}
	//else
	//{
	//	for (int i = 0; i < mPlayer.hp; i++) {
	//		DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
	//	}
	//}

}

void BackScroll()
{
	mScroll1 = mScroll1 - 5;
	if (mScroll1 <= -640) { mScroll1 = 640; }
	mScroll2 = mScroll2 - 5;
	if (mScroll2 <= -640) { mScroll2 = 640; }

	DrawGraph(mScroll1, 0, mImageBackground, TRUE);
	DrawGraph(mScroll2, 0, mImageBackground, TRUE);

}