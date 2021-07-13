#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include <math.h>

struct PLAYER mPlayer;

static int mImagePlayer[4];

float yadd = 0.0f;


void Player_Initialize() {

	SetTransColor(0, 0, 0);

	LoadDivGraph("images/Player.png", 4, 4, 1, 90, 84, mImagePlayer);
	mPlayer.flg = true;
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.angle = 0.0;
	mPlayer.count = 0;
	mPlayer.hp = PLAYER_HP;
	mPlayer.score = 0;
	mPlayer.r = PLAYER_HIT_R;
	mPlayer.jump = true;
}

void Player_Finalize() {
	for (int i = 0; i < 4; i++) {
		DeleteGraph(mImagePlayer[i]); 
	}
}

void Player_Update() 
{

	if (iNowKey & PAD_INPUT_UP && mPlayer.y == GROUND_HEIGHT)
	{
		yadd = -5.0f;
	}
	mPlayer.y += yadd;
	yadd += 0.2f;


	if (iNowKey & PAD_INPUT_LEFT) 
	{
		mPlayer.x -= PLAYER_SPEED;
		mPlayer.aruku++;
	}

	if (iNowKey & PAD_INPUT_RIGHT) 
	{
		mPlayer.x += PLAYER_SPEED;
		mPlayer.aruku++;
	}

	if (mPlayer.y > GROUND_HEIGHT) mPlayer.y = GROUND_HEIGHT;
	if (mPlayer.x < SCREEN_WIDTH_L + mPlayer.w / 2) mPlayer.x = SCREEN_WIDTH_L + mPlayer.w / 2;
	if (mPlayer.x > SCREEN_WIDTH_R - mPlayer.w / 2) mPlayer.x = SCREEN_WIDTH_R - mPlayer.w / 2;

	mPlayer.xi = mPlayer.aruku % 40 / 10;

	mPlayer.time++;
}

void Player_Draw() 
{

	if (mPlayer.flg) {
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.xi], TRUE, FALSE);
	}
	else {
		if (++mPlayer.count >= 80)	mPlayer.flg = true;
		if (mPlayer.count / 5 % 2 == 0) {
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer[mPlayer.xi], TRUE, FALSE);
		}
	}
}
