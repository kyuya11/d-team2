#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <math.h>


int HitCircleEnemy(PLAYER*, ENEMY*);

float yadd2 = 0.0f;


struct ENEMY mEnemy[ENEMY_MAX];
static int mImageEnemyKatatumuri;		
static int mImageEnemyKatatumuri_gyaku;
static int mImageEnemyKaeru;			
static int mImageEnemyKaeru_gyaku;		
static int mImageEnemyGa;				
static int mImageEnemyGa_gyaku;
static int mSoundsDamage;



void Enemy_Initialize() 
{
	mImageEnemyKatatumuri = LoadGraph("images/katatumuri3.png");	
	mImageEnemyKatatumuri_gyaku = LoadGraph("images/katatumuri_gyaku.png");	
	mImageEnemyKaeru = LoadGraph("images/kaeru6.png");	
	mImageEnemyKaeru_gyaku = LoadGraph("images/kaeru8.png");	
	mImageEnemyGa = LoadGraph("images/ga2.png");		
	mImageEnemyGa_gyaku = LoadGraph("images/ga4.png");
	mSoundsDamage = LoadSoundMem("sounds/damage.mp3");

	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		mEnemy[i].flg = FALSE;
	}
}

void Enemy_Finalize() 
{

	DeleteGraph(mImageEnemyKaeru);
	DeleteGraph(mImageEnemyKaeru_gyaku);

	DeleteGraph(mImageEnemyKatatumuri);
	DeleteGraph(mImageEnemyKatatumuri_gyaku);

	DeleteGraph(mImageEnemyGa);
	DeleteGraph(mImageEnemyGa_gyaku);

	StopSoundMem(mSoundsDamage);

}

void Enemy_Update() 
{
	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		if (mEnemy[i].flg == TRUE) 
		{

			mEnemy[i].x += mEnemy[i].mx;
			mEnemy[i].y += mEnemy[i].my;

			mEnemy[i].cnt++;

			switch (mEnemy[i].type) 
			{
			case 1: EnemyType01(&mEnemy[i]); break;	
			case 2: EnemyType02(&mEnemy[i]); break;	
			case 3: EnemyType03(&mEnemy[i]); break;	
			case 4: EnemyType04(&mEnemy[i]); break;
			case 5: EnemyType05(&mEnemy[i]); break;
			case 6: EnemyType06(&mEnemy[i]); break;
			}

			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) 
			{
				mEnemy[i].y = 370;
			}
			if (mEnemy[i].x > SCREEN_WIDTH + mEnemy[i].w) 
			{
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) 
			{
				mEnemy[i].flg = FALSE;
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE) 
			{
				if (mPlayer.flg == true) 
				{
					mPlayer.hp -= 1;
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mEnemy[i].flg = FALSE;
					PlaySoundMem(mSoundsDamage, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

//•`‰æ
void Enemy_Draw() 
{
	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		if (mEnemy[i].flg == TRUE) 
		{
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);
		}
	}

}

int CreateEnemy(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		if (mEnemy[i].flg == FALSE) 
		{
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


void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->x == 0) 
	{
		mEnemy->mx = 1;
		mEnemy->img = mImageEnemyKatatumuri_gyaku;
		mEnemy->kieru++;
	}

	if (mEnemy->x == 640 && mEnemy->kieru <= 1) 
	{
		mEnemy->flg = false;
	}

}

void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->x == 1) 
	{
		mEnemy->img = mImageEnemyKatatumuri_gyaku;
	}
}

void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) 
	{
		mEnemy->yadd2 = -5.0f;
	}
	mEnemy->y += mEnemy->yadd2;
	mEnemy->yadd2 += 0.2f;

}

void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) 
	{
		mEnemy->yadd2 = -5.0f;
	}
	mEnemy->y += mEnemy->yadd2;
	mEnemy->yadd2 += 0.2f;

	if (mEnemy->x == 1) 
	{
		mEnemy->img = mImageEnemyKaeru_gyaku;
	}

}


void EnemyType05(ENEMY* mEnemy)
{

	if (mEnemy->cnt % 20 == 0) 
	{
		mEnemy->my = 1;
	}
	if (mEnemy->cnt % 40 == 0) 
	{
		mEnemy->my = -1;
	}
}


void EnemyType06(ENEMY* mEnemy)
{
	if (mEnemy->x == 1) 
	{
		mEnemy->img = mImageEnemyGa_gyaku;
	}

	if (mEnemy->cnt % 20 == 0) 
	{
		mEnemy->my = 1;
	}
	if (mEnemy->cnt % 40 == 0) 
	{
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




