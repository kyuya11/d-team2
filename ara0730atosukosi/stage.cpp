#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include <stdlib.h>

void Stage1()
{
	int mGameTime = Game_GetmGameTime();

	if (mGameTime < 51)
	{
		if (mGameTime % 50 == 0) {
			CreateEnemy(1, 1, 640, 370, 70, 50, -1, 0);
			CreateEnemy(2, 1, 0, 370, 70, 50, 1, 0);
			CreateEnemy(3, 1, 640, 370, 43, 35, -1, 0);
			CreateEnemy(4, 1, 0, 370, 43, 35, 1, 0);
			CreateEnemy(5, 1, 640, 145, 45, 35, -1, -1);
			CreateEnemy(6, 1, 0, 145, 45, 35, 1, -1);
		}
	}
}
//
//
///**********************************
//* ƒXƒe[ƒW‚P
//* ˆø ”F‚È‚µ
//* –ß‚è’lF‚È‚µ
//**********************************/
//void Stage1()
//{
//	int mGameTime = Game_GetmGameTime();
//
//	if (mGameTime % 700 == 0)
//	{
//		CreateItem(3, 1, rand() % 430 + 50, -10, 66, 50, 0, 1);
//	}
//
//	if (mGameTime < 100);
//	else if (mGameTime < 325)
//	{
//		if (mGameTime % 25 == 0)
//		{
//			//ƒAƒCƒeƒ€‚ðŽç‚Á‚Ä‚¢‚é‚æ‚¤‚Éo‚Ä‚­‚é
//			CreateEnemy(2, 0, 180, -10, 23, 26, 0, 1);
//			CreateEnemy(1, 0, 280, -10, 23, 26, 0, 1);
//
//
//		}
//		if (mGameTime == 200)
//		{
//			CreateItem(1, 0, 237, -10, 66, 50, 0, 1);
//
//		}
//	}
//	else if (mGameTime < 400);
//	else if (mGameTime < 600)
//	{
//		if (mGameTime < 500)
//		{
//
//		}
//		if (mGameTime % 25 == 0)
//		{
//			//¶‚Æ‰E‚©‚ç—H—ì‚ªo‚Ä‚«‚Äs‚­Žè‚ð‘j‚Þ
//			CreateEnemy(3, 0, 1, 170, 23, 26, 3, 0);
//			CreateEnemy(4, 0, 440, 210, 23, 26, -3, 0);
//			CreateEnemy(3, 0, 1, 250, 23, 26, 3, 0);
//			CreateEnemy(4, 0, 440, 290, 23, 26, -3, 0);
//		}
//	}
//	else if (mGameTime < 800)
//	{
//		if (mGameTime == 790)
//		{
//			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);
//
//		}
//
//		if (mGameTime % 25 == 0)
//		{
//			//ƒWƒOƒUƒO‚É‰º‚ÉˆÚ“®‚µ‚È‚ª‚çUŒ‚‚µ‚Ä‚­‚é–Ú‹Ê
//			CreateEnemy(11, 1, 230, -10, 44, 41, 0, 1);
//
//		}
//	}
//	else if (mGameTime < 850)
//	{
//		//ƒAƒCƒeƒ€‚ªˆêŒÂ‚¾‚¯o‚Ä‚­‚é
//		if (mGameTime == 820)
//		{
//			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);
//		}
//	}
//	else if (mGameTime < 1000);
//	else if (mGameTime < 1200)
//	{
//
//		if (mGameTime % 25 == 0)
//		{
//			//“r’†‚ÅŒð·‚·‚é—H—ì
//			CreateEnemy(1, 0, 440, -10, 23, 26, -2, 1);
//			CreateEnemy(2, 0, 0, -10, 23, 26, 2, 1);
//
//			CreateItem(1, 0, 230, -10, 66, 50, 0, 1);
//
//		}
//		if (mGameTime == 1025)
//		{
//			CreateItem(1, 0, 230, -10, 66, 50, 0, 1);
//
//		}
//	}
//	else if (mGameTime < 1300);
//	else if (mGameTime < 1340)
//	{
//		if (mGameTime % 50 == 0)
//		{
//			//“G‚ªŒð·‚µ‚Ä‚Å‚Ä‚­‚é‚â‚Â
//			CreateEnemy(9, 0, 1, 50, 44, 41, 4, 0);			//“G‚ª¶‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
//			CreateEnemy(10, 0, 440, 50, 44, 41, -4, 0);		//“G‚ª‰E‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
//
//			CreateEnemy(9, 0, 1, 100, 44, 41, 1, 0);		//“G‚ª¶‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
//			CreateEnemy(10, 0, 440, 100, 44, 41, -1, 0);		//“G‚ª‰E‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
//		}
//	}
//	else if (mGameTime < 1750);
//	else if (mGameTime < 1950)
//	{
//		if (mGameTime % 25 == 0)
//		{
//			//ã‚©‚çŒð·‚µ‚È‚ª‚ç‰º‚É~‚è‚Ä‚­‚é
//			CreateEnemy(5, 0, 180, -10, 23, 26, 0, 2);
//			CreateEnemy(6, 0, 280, -10, 23, 26, 0, 2);
//		}
//		if (mGameTime % 200 == 0)
//		{
//			//¶‚©‚ço‚Ä¶‚É•À‚Ô–Ú‹Ê
//			CreateEnemy(12, 0, 0, 150, 44, 41, 4, 0);
//			CreateEnemy(12, 0, 0, 250, 44, 41, 2, 0);
//			CreateEnemy(12, 0, 0, 350, 44, 41, 1, 0);
//
//			//‰E‚©‚ço‚Ä‰E‚É•À‚Ô–Ú‹Ê
//			CreateEnemy(13, 0, 440, 150, 44, 41, -4, 0);
//			CreateEnemy(13, 0, 440, 250, 44, 41, -2, 0);
//			CreateEnemy(13, 0, 440, 350, 44, 41, -1, 0);
//		}
//
//	}
//	else if (mGameTime < 2000)
//	{
//		if (mGameTime % 50 == 0)
//		{
//
//		}
//	}
//	else if (mGameTime < 2100);
//	else if (mGameTime < 2140)
//	{
//		if (mGameTime % 50 == 0)
//		{
//
//		}
//	}
//
//	else if (mGameTime < 2300);
//	else if (mGameTime < 2540)
//	{
//		if (mGameTime == 2480)
//		{
//			//ƒ{ƒX
//			CreateEnemy(14, 1, 230, -10, 96, 64, 0, 1);
//		}
//
//		if (mGameTime == 2500)
//		{
//			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);
//		}
//
//	}
//
//	else if (mGameTime < 3200);
//	else if (mGameTime == 5000)
//	{
//		Game_SetmgameStatus(false);
//	}
//}