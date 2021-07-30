#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include <math.h>


int HitCircleEnemy(PLAYER*, ENEMY*);	//敵の当たり判定




struct ENEMY mEnemy[ENEMY_MAX];	//
static int mImageEnemyKatatumuri;		//
static int mImageEnemyKatatumuri_gyaku;//
static int mImageEnemyKaeru;			//
static int mImageEnemyKaeru_gyaku;		//
static int mImageEnemyGa;				//
static int mImageEnemyGa_gyaku;		//


void Enemy_Initialize() {
	mImageEnemyKatatumuri = LoadGraph("images/katatumuri3.png");	//敵：カタツムリ　画像
	mImageEnemyKatatumuri_gyaku = LoadGraph("images/katatumuri_gyaku.png");	//敵：カタツムリ　反転画像
	mImageEnemyKaeru = LoadGraph("images/kaeru6.png");	//敵：カエル
	mImageEnemyKaeru_gyaku = LoadGraph("images/kaeru8.png");	//敵：カエル　反転画像
	mImageEnemyGa = LoadGraph("images/ga2.png");		//敵：蛾　画像
	mImageEnemyGa_gyaku = LoadGraph("images/ga4.png");	//敵：蛾　反転画像


	for (int i = 0; i < ENEMY_MAX; i++) {	//エネミーの数だけ初期化
		mEnemy[i].flg = FALSE;
	}
}

//終了処理
void Enemy_Finalize()
{
	//カエル　画像の解放
	DeleteGraph(mImageEnemyKaeru);
	DeleteGraph(mImageEnemyKaeru_gyaku);

	//カタツムリ　画像の解放
	DeleteGraph(mImageEnemyKatatumuri);
	DeleteGraph(mImageEnemyKatatumuri_gyaku);

	//蛾　画像の解放
	DeleteGraph(mImageEnemyGa);
	DeleteGraph(mImageEnemyGa_gyaku);
}

void Enemy_Update() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {

			mEnemy[i].x += mEnemy[i].mx;	//mx で移動するためx座標に mx に入れた値だけ移動する
			mEnemy[i].y += mEnemy[i].my;	//my で移動するためx座標に my に入れた値だけ移動する

			mEnemy[i].cnt++;				//エネミーが現れてからのカウントを1ずつ増やす

			switch (mEnemy[i].type)			//敵の種類を分けるため
			{
			case 1: EnemyType01(&mEnemy[i]); break;	//カタツムリ
			case 2: EnemyType02(&mEnemy[i]); break;	//カタツムリ
			case 3: EnemyType03(&mEnemy[i]); break;	//カエル
			case 4: EnemyType04(&mEnemy[i]); break;
			case 5: EnemyType05(&mEnemy[i]); break;
			case 6: EnemyType06(&mEnemy[i]); break;
			}

			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {	//地面の高さ決め
				mEnemy[i].y = 370;
			}
			if (mEnemy[i].x > SCREEN_WIDTH + mEnemy[i].w) {		//敵が画面右に行った場合消去
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {				//敵が画面左に行った場合消去
				mEnemy[i].flg = FALSE;
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE)
			{
				mPlayer.flg = FALSE;
				mPlayer.count = 0;
				mPlayer.hp -= 1;
				mEnemy[i].flg = FALSE;
			}
		}
	}
}

//描画
void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == TRUE) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);
		}
	}

}

int CreateEnemy(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;

			if (type == 1 || type == 2)
			{
				mEnemy[i].img = mImageEnemyKatatumuri;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			if (type == 3 || type == 4)
			{
				mEnemy[i].img = mImageEnemyKaeru;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			if (type == 5 || type == 6)
			{
				mEnemy[i].img = mImageEnemyGa;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			mEnemy[i].x = x;
			mEnemy[i].y = y;
			mEnemy[i].w = w;
			mEnemy[i].h = h;
			mEnemy[i].mx = mx;
			mEnemy[i].my = my;
			mEnemy[i].cnt = 0;
			mEnemy[i].kieru = 0;
			mEnemy[i].yadd2 = 0.0f;


			return TRUE;
		}
	}

	return FALSE;
}

/*
カタツムリ：右から出てきて折り返して消える
*/
void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->x == 0) {
		mEnemy->mx = 1;
		mEnemy->img = mImageEnemyKatatumuri_gyaku;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 640 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}

}
/*
カタツムリ：左から出てきて折り返して消える
*/
void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->x == 1) {
		mEnemy->img = mImageEnemyKatatumuri_gyaku;
	}

	if (mEnemy->x == 640) {
		mEnemy->mx = -1;
		mEnemy->img = mImageEnemyKatatumuri;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 0 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}


}

/*
カエル：右から跳ねながら出てきて折り返して消える
*/
void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) {
		mEnemy->yadd2 = -5.0f;
	}
	mEnemy->y += mEnemy->yadd2;
	mEnemy->yadd2 += 0.2f;

	if (mEnemy->x == 0) {
		mEnemy->mx = 1;
		mEnemy->img = mImageEnemyKaeru_gyaku;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 640 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}

}

/*
カエル：左から跳ねながら出てきて折り返して消える
*/
void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) {
		mEnemy->yadd2 = -5.0f;
	}
	mEnemy->y += mEnemy->yadd2;
	mEnemy->yadd2 += 0.2f;

	if (mEnemy->x == 1) {
		mEnemy->img = mImageEnemyKaeru_gyaku;
	}

	if (mEnemy->x == 640) {
		mEnemy->mx = -1;
		mEnemy->img = mImageEnemyKaeru;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 0 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}
}

/*
蛾：右からフラフラしながら出てきて折り返して消える
*/
void EnemyType05(ENEMY* mEnemy)
{
	if (mEnemy->x == 0) {
		mEnemy->mx = 1;
		mEnemy->img = mImageEnemyGa_gyaku;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 640 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}

	if (mEnemy->cnt % 20 == 0) {
		mEnemy->my = 1;
	}
	if(mEnemy->cnt % 40 == 0){
		mEnemy->my = -1;
	}
}

/*
蛾：左からフラフラしながら出てきて折り返して消える
*/
void EnemyType06(ENEMY* mEnemy)
{
	if (mEnemy->x == 1) {
		mEnemy->img = mImageEnemyGa_gyaku;
	}

	if (mEnemy->x == 640) {
		mEnemy->mx = -1;
		mEnemy->img = mImageEnemyGa;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 0 && mEnemy->kieru <= 1) {
		mEnemy->flg = false;
	}

	if (mEnemy->cnt % 20 == 0) {
		mEnemy->my = 1;
	}
	if (mEnemy->cnt % 40 == 0) {
		mEnemy->my = -1;
	}
}

int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}




