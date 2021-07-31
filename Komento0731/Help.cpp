#include "Help.h"
#include "Scene.h"
#include "DxLib.h"
#include "Input.h"

static int mImageHandle;	//画像格納用変数
static int WaitTime;		//待ち時間

/***********************************************
 * ヘルプ 初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Initialize() {
	mImageHandle = LoadGraph("images/haikei3.png");	//画像のロード
	WaitTime = 0;	//待ち時間初期化
}


/***********************************************
 * ヘルプ 終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Finalize() {
	DeleteGraph(mImageHandle);	//画像の解放
}


/***********************************************
 * ヘルプ 更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {	//YボタンとESCキーで
		SceneMgr_ChangeScene(eScene_Menu);	//シーンをメニューに移行
	}
}


/***********************************************
 * ヘルプ 描画
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);	//ゲーム背景描画

	SetFontSize(30);

	DrawString(100, 150, "・左、右キーで移動。←→", GetColor(0, 0, 255));
	DrawString(100, 200, "・上キーでジャンプ。↑", GetColor(0, 0, 255));
	DrawString(100, 250, "・時間内の間は敵を避けまくろう。", GetColor(255, 0, 0));
	DrawString(100, 300, "・HPが0になるとゲームオーバー!", GetColor(255, 0, 0));


	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "EscキーまたはBボタンを押すとメニュー画面に戻ります。",
			GetColor(0, 0, 0));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}