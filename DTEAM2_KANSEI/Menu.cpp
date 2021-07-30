#include "DxLib.h"
#include "Scene.h"
#include "Menu.h"
#include "Input.h"

static int mImageHandle; 
static int mImageSelect; 
static int MenuNumber = 0; 

static int mSoundsSelect; 
static int mSoundsMove; 

void Menu_Initialize()
{
	mImageHandle = LoadGraph("images/title.png"); 
	mImageSelect = LoadGraph("images/select.png"); 

	mSoundsSelect = LoadSoundMem("sounds/kettei.mp3");    
	mSoundsMove = LoadSoundMem("sounds/select.mp3"); 
	PlayMusic("sounds/kouhoBGM3.mp3", DX_PLAYTYPE_LOOP);
}

void Menu_Finalize()
{
	DeleteGraph(mImageHandle);
	DeleteGraph(mImageSelect); 

	StopSoundMem(mSoundsSelect);
	StopSoundMem(mSoundsMove); 

	StopMusic();

}

void Menu_Update() 
{
	if (iKeyFlg & PAD_INPUT_DOWN) 
	{
		PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
		if (++MenuNumber > 2) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) 
	{
		PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 2;
	}

	if (iKeyFlg == PAD_INPUT_1) 
	{ 
		PlaySoundMem(mSoundsSelect, DX_PLAYTYPE_BACK);
		WaitTimer(500);
		switch (MenuNumber) { 
		case 0:
			SceneMgr_ChangeScene(eScene_Game); 
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Help); 
			break;
		case 2:
			SceneMgr_ChangeScene(eScene_End);
			break;

		}
	}

}

void Menu_Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);

	DrawRotaGraph(240, 187 + MenuNumber * 61, 1.0f, 1.0f, mImageSelect, TRUE);

}
