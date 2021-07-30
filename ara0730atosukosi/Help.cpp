#include "Help.h"
#include "Scene.h"
#include "DxLib.h"
#include "Input.h"

static int mImageHandle;
static int WaitTime;

void Help_Initialize() {
	mImageHandle = LoadGraph("images/haikei3.png");
	WaitTime = 0;
}

void Help_Finalize() {
	DeleteGraph(mImageHandle);
}

void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Help_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);

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