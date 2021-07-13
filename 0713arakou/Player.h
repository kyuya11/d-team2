#pragma once

#define PI 3.1415926535897932384626433832795f

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 630;
const int SCREEN_WIDTH_L = 10;
const int GROUND_HEIGHT = 380;

const int PLAYER_POS_X = 100;
const int PLAYER_POS_Y = 380;
const int PLAYER_WIDTH = 60;
const int PLAYER_HEIGHT = 56;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 5;
const int PLAYER_HIT_R = 3;

struct PLAYER {
	bool flg;
	int x, y;
	int w, h;
	double angle;
	int count;
	int kougekicount;
	int hp;
	int time;
	int score;
	int r;
	int aruku;
	int xi;
	bool jump;
};

extern struct PLAYER mPlayer;

extern void Player_Initialize();//èâä˙âª
extern void Player_Finalize();//èIóπèàóù
extern void Player_Update();//çXêV
extern void Player_Draw();//ï`âÊ