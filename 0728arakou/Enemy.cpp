#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include <math.h>


int HitCircleEnemy(PLAYER*, ENEMY*);

float yadd2 = 0.0f;


struct ENEMY mEnemy[ENEMY_MAX];
int mImageEnemyKatatumuri;
int mImageEnemyKatatumuri_gyaku;
int mImageEnemyKaeru;
int mImageEnemyTyou;


void Enemy_Initialize() {
	mImageEnemyKatatumuri = LoadGraph("images/katatumuri3.png");
	mImageEnemyKatatumuri_gyaku = LoadGraph("images/katatumuri_gyaku.png");
	mImageEnemyKaeru = LoadGraph("images/kaeru4.png");
	mImageEnemyTyou = LoadGraph("images/musi.png");


	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
	}
}

//I—¹ˆ—
void Enemy_Finalize() 
{

	DeleteGraph(mImageEnemyKaeru);


	DeleteGraph(mImageEnemyKatatumuri); 
	DeleteGraph(mImageEnemyKatatumuri_gyaku);
	DeleteGraph(mImageEnemyTyou);
}

void Enemy_Update() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {

			mEnemy[i].x += mEnemy[i].mx;
			mEnemy[i].y += mEnemy[i].my;

			mEnemy[i].cnt++;

			switch (mEnemy[i].type) 
			{
				case 1: EnemyType01(&mEnemy[i]); break;
				case 2: EnemyType02(&mEnemy[i]); break;
				case 3: EnemyType03(&mEnemy[i]); break;
			}

			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {
				mEnemy[i].y = 370;
			}
			if (mEnemy[i].x > SCREEN_WIDTH + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE) 
			{
				mEnemy[i].flg = FALSE;
			}
		}
	}
}

//•`‰æ
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

			if (type == 1) 
			{
				mEnemy[i].img = mImageEnemyKatatumuri;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			if (type == 2)
			{
				mEnemy[i].img = mImageEnemyKaeru;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			if (type == 3)
			{
				mEnemy[i].img = mImageEnemyTyou;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			mEnemy[i].x = x;
			mEnemy[i].y = y;
			mEnemy[i].w = w;
			mEnemy[i].h = h;
			mEnemy[i].mx = mx;
			mEnemy[i].my = my;
			mEnemy[i].cnt = 0;
			mEnemy[i].bosu = 0;


			return TRUE;
		}
	}

	return FALSE;
}


void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->cnt % 200 == 0) {
		mEnemy->mx = 1;
		mEnemy->img = mImageEnemyKatatumuri_gyaku;
	}
	if (mEnemy->cnt % 400 == 0) {
		mEnemy->mx = -1;
		mEnemy->img = mImageEnemyKatatumuri;
	}
}
void EnemyType02(ENEMY* mEnemy)
{

	if (mEnemy->y == 370) {
		yadd2 = -7.0f;
	}
	mEnemy->y += yadd2;
	yadd2 += 0.2f;

}
void EnemyType03(ENEMY* mEnemy)
{

	if (mEnemy->cnt % 200 == 0) {
		mEnemy->mx = 1;
	}
	if (mEnemy->cnt % 400 == 0) {
		mEnemy->mx = -1;
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




