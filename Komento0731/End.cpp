#include "End.h"
#include "Scene.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //画像ハンドル格納用変数
static int StopTime;	//時間制限

//初期化
void End_Initialize() {
	mImageHandle = LoadGraph("images/End.png");//画像のロード
	StopTime = 0;		//時間制限の初期化
}

//終了処理
void End_Finalize() {
	DeleteGraph(mImageHandle);//画像の解放
}


//描画
void End_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);	//画像を描画

	SetFontSize(25);
	DrawString(340, 456, "Thank you for Playing", 0xff0000, 0);

	//タイムの加算処理＆終了 (２秒後)
	if (++StopTime > 120) {
		SceneMgr_ChangeScene(eScene_Stop); //シーンをゲーム画面に変更
	}
}