#pragma once

#define PI 3.1415926535897932384626433832795f

//画面領域の大きさ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 630;
const int SCREEN_WIDTH_L = 10;
const int GROUND_HEIGHT = 340;

const int PLAYER_POS_X = 320;
const int PLAYER_POS_Y = 340;
const int PLAYER_WIDTH = 60;
const int PLAYER_HEIGHT = 56;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 3;
const int PLAYER_HIT_R = 30;	//衝突判定の半径


/*************************
** 構造体 **
*************************/
//プレイヤー
struct PLAYER {
	bool flg;		//使用フラグ
	int x, y;		//座標x、y
	int w, h;		//幅ｗ、高さｈ
	double angle;	//プレイヤーの向き
	int count;		//復活間隔
	int hp;			//体力
	int time;		//経過時間
	int r;			//半径
	int aruku;		//
	int xi;			//
	bool jump;		//ジャンプ
	int result;		//結果
};

extern struct PLAYER mPlayer;

extern void Player_Initialize();//初期化
extern void Player_Finalize();//終了処理
extern void Player_Update();//更新
extern void Player_Draw();//描画