#pragma once

#define PI 3.1415926535897932384626433832795f

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 630;
const int SCREEN_WIDTH_L = 10;
const int GROUND_HEIGHT = 340;

const int PLAYER_POS_X = 320;
const int PLAYER_POS_Y = 340;
const int PLAYER_WIDTH = 60;
const int PLAYER_HEIGHT = 56;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 3;
const int PLAYER_HIT_R = 30;

struct PLAYER {
	bool flg;
	int x, y;
	int w, h;
	double angle;
	int count;
	int hp;
	int time;
	int r;
	int aruku;
	int xi;
	bool jump;
	int result;
};

extern struct PLAYER mPlayer;

extern void Player_Initialize();//������
extern void Player_Finalize();//�I������
extern void Player_Update();//�X�V
extern void Player_Draw();//�`��