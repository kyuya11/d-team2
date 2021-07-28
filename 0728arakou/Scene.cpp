#include "DxLib.h"
#include "Scene.h"
#include "Menu.h"
#include "Game.h"
#include "End.h"

static eScene mScene = eScene_Menu;
static eScene mNextScene = eScene_None;

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

void SceneMgr_Update() {
	if (mNextScene != eScene_None) {
		SceneMgr_FinalizeModule(mScene);
		mScene = mNextScene;
		mNextScene = eScene_None;
		SceneMgr_InitializeModule(mScene);
	}
	switch (mScene) { 
	case eScene_Menu: 
		Menu_Update(); 
		break;
	case eScene_Game:
		Game_Update();
		break;
	//case eScene_Help:
	//	Help_Update();
	//	break;
	}
}

void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Menu: 
		Menu_Draw();
		break;
	case eScene_Game:
		Game_Draw();
		break;
	//case eScene_Help:
	//	Help_Draw();
	//	break;
	case eScene_End:
		End_Draw();
		break;
	}
}

void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene; 
}


int SceneMgr_GameEnd_Status() {
	if (mScene == eScene_Stop) {
		return 1;
	}
	else {
		return 0;
	}
}


static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) { 
	case eScene_Menu:
		Menu_Initialize();
		break;
	case eScene_Game:
		Game_Initialize();
		break;
	//case eScene_Help:
	//	Help_Initialize();
	//	break;
	case eScene_End:
		End_Initialize();
		break;
	}
}

static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) { 
	case eScene_Menu: 
		Menu_Finalize(); 
		break;
	case eScene_Game:
		Game_Finalize();
		break;
	//case eScene_Help:
	//	Help_Finalize();
	//	break;
	case eScene_End:
		End_Finalize();
		break;
	}
}