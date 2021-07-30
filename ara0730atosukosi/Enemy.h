#pragma once

#define PI 3.1415926535897932384626433832795f

const int ENEMY_MAX = 100;
const int ENEMY_IMAGE_MAX = 2;


const int ENEMY_ZAKO_HIT_R = 9;

struct ENEMY {
	bool flg; 
	int type; 
	int img; 
	int x, y, w, h; 
	int mx, my;
	int cnt; 
	int r; 
	int kieru;	
	float yadd2;
};

extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();
extern void Enemy_Finalize();
extern void Enemy_Update();
extern void Enemy_Draw();

int CreateEnemy(int, int, int, int, int, int, int, int);

void EnemyType01(ENEMY*);
void EnemyType02(ENEMY*);
void EnemyType03(ENEMY*);
void EnemyType04(ENEMY*);
void EnemyType05(ENEMY*);
void EnemyType06(ENEMY*);
