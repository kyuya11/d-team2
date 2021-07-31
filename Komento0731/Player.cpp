#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include <math.h>

struct PLAYER mPlayer;	//自機

static int mImagePlayer[8];	//画像ハンドル格納用変数
static int mSoundsJump;		//音ファイル格納用変数

float yadd = 0.0f;			//ジャンプ力


/***********************************************
 * プレイヤー　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Initialize()
{
	LoadDivGraph("images/player.png", 8, 4, 2, 90, 81, mImagePlayer);	//プレイヤー画像
	mSoundsJump = LoadSoundMem("sounds/jump.mp3");						//ジャンプ音のロード

	//プレイヤーの初期設定
	mPlayer.flg = true;
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.angle = 0.0;
	mPlayer.count = 0;
	mPlayer.hp = PLAYER_HP;
	mPlayer.r = PLAYER_HIT_R;
	mPlayer.jump = true;
	mPlayer.aruku = 0;
	mPlayer.result = 4;
	mPlayer.hp = PLAYER_HP;
}



/***********************************************
 * プレイヤー　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Finalize()
{
	StopSoundMem(mSoundsJump);	//ジャンプ音停止


	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(mImagePlayer[i]);	//画像の解放
	}

}


/***********************************************
 * プレイヤー　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Update()
{

	if (iNowKey & PAD_INPUT_UP && mPlayer.y == GROUND_HEIGHT)	//上キーを押したら、かつ、地面の高さだったら
	{
		PlaySoundMem(mSoundsJump, DX_PLAYTYPE_BACK);	//ジャンプ音

		yadd = -7.0f;	//ジャンプ力
	}
	mPlayer.y += yadd;	//y軸に加算
	yadd += 0.2f;		//加算


	if (iNowKey & PAD_INPUT_LEFT)	//左キーを押したら
	{
		mPlayer.x -= PLAYER_SPEED;

		if (mPlayer.aruku > 0)
		{
			mPlayer.aruku = 0;
		}

		mPlayer.aruku--;

	}
	if (iNowKey & PAD_INPUT_RIGHT)	//右キーを押したら
	{
		mPlayer.x += PLAYER_SPEED;

		if (mPlayer.aruku < 0)
		{
			mPlayer.aruku = 0;
		}

		mPlayer.aruku++;
	}



	// 画面をはみ出さないようにする
	if (mPlayer.y > GROUND_HEIGHT) mPlayer.y = GROUND_HEIGHT;
	if (mPlayer.x < SCREEN_WIDTH_L + mPlayer.w / 2) mPlayer.x = SCREEN_WIDTH_L + mPlayer.w / 2;
	if (mPlayer.x > SCREEN_WIDTH_R - mPlayer.w / 2) mPlayer.x = SCREEN_WIDTH_R - mPlayer.w / 2;

	mPlayer.xi = abs(mPlayer.aruku) % 40 / 10;

	if (mPlayer.aruku > 0)
	{
		mPlayer.xi += 4;

		mPlayer.result = mPlayer.xi;
	}
	else if (mPlayer.aruku < 0)
	{
		mPlayer.result = mPlayer.xi;
	}

	mPlayer.time++;	//経過時間
}


/***********************************************
 * プレイヤー　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Draw()
{
	//プレイヤーの表示
	if (mPlayer.flg)
	{
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.result], TRUE, FALSE);
	}
	else
	{
		// プレイヤー復活までの時間3秒（180フレーム）
		if (++mPlayer.count >= 80)	mPlayer.flg = true;
		if (mPlayer.count / 5 % 2 == 0) {
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.result], TRUE, FALSE);
		}
	}
}
