#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include <stdlib.h>

void Stage1()
{
	int mGameTime = Game_GetmGameTime();


	if (mGameTime % (rand() % 300 + 50) == 0) 
	{
		CreateEnemy(1, 1, 640, 370, 70, 50, -1, 0);
	}
	if (mGameTime % (rand() % 300 + 100) == 0)
	{
		CreateEnemy(2, 1, 0, 370, 70, 50, 1, 0);
	}

	if (mGameTime % (rand() % 300 + 100) == 0)
	{
		CreateEnemy(3, 1, 640, 370, 43, 35, -1, 0);
	}
	if (mGameTime % (rand() % 300 + 50) == 0)
	{
		CreateEnemy(4, 1, 0, 370, 43, 35, 1, 0);
	}

	if (mGameTime % (rand() % 300 + 50) == 0)
	{
		CreateEnemy(5, 1, 640, rand() % 145 + 125, 45, 35, -1, -1);
	}
	if (mGameTime % (rand() % 300 + 100) == 0)
	{
		CreateEnemy(6, 1, 0, rand() % 145 + 125, 45, 35, 1, -1);
	}

}