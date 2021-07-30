#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include <math.h>

struct PLAYER mPlayer;

static int mImagePlayer[8];
static int mSoundsJump;

float yadd = 0.0f;


void Player_Initialize() 
{
	LoadDivGraph("images/player.png", 8, 4, 2, 90, 81, mImagePlayer);
	mSoundsJump = LoadSoundMem("sounds/jump.mp3");


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

void Player_Finalize() 
{
	StopSoundMem(mSoundsJump);


	for (int i = 0; i < 8; i++) 
	{
		DeleteGraph(mImagePlayer[i]); 
	}

}

void Player_Update() 
{

	if (iNowKey & PAD_INPUT_UP && mPlayer.y == GROUND_HEIGHT)
	{
		PlaySoundMem(mSoundsJump, DX_PLAYTYPE_BACK);

		yadd = -7.0f;
	}
	mPlayer.y += yadd;
	yadd += 0.2f;


	if (iNowKey & PAD_INPUT_LEFT) 
	{
		mPlayer.x -= PLAYER_SPEED;

		if (mPlayer.aruku > 0)
		{
			mPlayer.aruku = 0;
		}

		mPlayer.aruku--;

	}
	if (iNowKey & PAD_INPUT_RIGHT)
	{
		mPlayer.x += PLAYER_SPEED;

		if (mPlayer.aruku < 0)
		{
			mPlayer.aruku = 0;
		}

		mPlayer.aruku++;
	}

	


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

	mPlayer.time++;
}

void Player_Draw() 
{

	if (mPlayer.flg) 
	{
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.result], TRUE, FALSE);
	}
	else 
	{
		if (++mPlayer.count >= 80)	mPlayer.flg = true;
		if (mPlayer.count / 5 % 2 == 0) {
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.result], TRUE, FALSE);
		}
	}
}
