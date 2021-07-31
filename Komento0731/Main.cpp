#include "DxLib.h"
#include "Scene.h"
#include "Input.h"




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//タイトルを設定、ウィンドウモード変更、DXライブラリ初期化、裏画面設定
	SetMainWindowText("YOKERO"), ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	
	SceneMgr_Initialize();	//初期化

	while (ProcessMessage() == 0) {	//メッセージ処理

		if (SceneMgr_GameEnd_Status()) {
			break;	//メニューから終了を選択
		}

		ClearDrawScreen();	//画面消去

		InputKey();			//入力
		
		SceneMgr_Update();	//更新
		SceneMgr_Draw();	//描画


		ScreenFlip();		//画面更新

	}
	SceneMgr_Finalize();


	DxLib_End();	//DXライブラリ終了処理
	return 0;
}