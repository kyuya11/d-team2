#pragma once

#define PI 3.1415926535897932384626433832795f

const int ENEMY_MAX = 9;		//敵の最大数
const int ENEMY_IMAGE_MAX = 3;	//敵の画像の最大数


const int ENEMY_ZAKO_HIT_R = 9;	//敵の当たり判定

//エネミー構造体
struct ENEMY {
	bool flg;		//敵がいるかいなかの管理
	int type;		//敵の種類の管理
	int img;		//敵の画像の管理
	int x, y, w, h;	//敵のx座標、y座標、高さ、横幅の管理
	int mx, my;		//敵のx軸に対しての移動量、y軸に対しての移動量の管理
	int cnt;		//敵が出現してからのカウントの管理
	int r;			//敵の半径の管理
	float yadd2;	//敵のジャンプ力の管理
};

extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();	//初期化
extern void Enemy_Finalize();	//終了処理
extern void Enemy_Update();		//更新
extern void Enemy_Draw();		//描画

int CreateEnemy(int, int, int, int, int, int, int, int);	//敵の構造

void EnemyType01(ENEMY*);	//エネミータイプ01の移動
void EnemyType02(ENEMY*);	//エネミータイプ02の移動
void EnemyType03(ENEMY*);	//エネミータイプ03の移動
void EnemyType04(ENEMY*);	//エネミータイプ04の移動
void EnemyType05(ENEMY*);	//エネミータイプ05の移動
void EnemyType06(ENEMY*);	//エネミータイプ06の移動
