#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "stage.h"
#include "Help.h"

/*************************
** Game.cpp���ϐ� **
*************************/
static int mImageHandle;		//�摜�n���h���i�[�p
static int mImageBackground;	//�摜�n���h���i�[�p
static int mImageHp;			//�摜�n���h���i�[�p
static int mgameStatus;			//�Q�[���X�e�[�^�X�ϐ�

static int Seigen;				//���Ԑ����p�ϐ�
static int mGameTime;			//�Q�[���o�ߎ���
static int StartTime;			//�X�^�[�g�p�ϐ�


/***********************************************
 * �Q�[���@������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Initialize()
{
	mImageBackground = LoadGraph("images/haikei3.png");	//�摜�̃��[�h

	mImageHp = LoadGraph("images/select.png");			//�摜�̃��[�h


	PlayMusic("sounds/kouhoBGM2.mp3", DX_PLAYTYPE_LOOP);//�Q�[����BGM�Đ�


	Player_Initialize();
	Enemy_Initialize();

	StartTime = GetNowCount();	//�o�߂������l������

	Seigen = 1;

	mGameTime = 0;

	mgameStatus = TRUE;
}


/***********************************************
 * �Q�[���@�I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Finalize()
{
	DeleteGraph(mImageHandle);

	StopMusic();

	Player_Finalize();
	Enemy_Finalize();

}


/***********************************************
 * �Q�[���@�X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Update()
{
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) //Y�{�^���܂���ESC�L�[��
	{
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}

	//�Q�[���v���C���X�V
	Player_Update();
	Enemy_Update();

	mGameTime++;

	Stage1();
}

/***********************************************
 * �Q�[���@�`�揈��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Draw()
{

	if (mPlayer.hp > 0 && Seigen > 0)
	{
		Player_Draw();
		Enemy_Draw();
		GameTime();
	}

	if (mPlayer.hp <= 0 && mgameStatus == TRUE)
	{
		GameOver();
	}
	if (Seigen <= 0)
	{
		GameFinish();
	}
	else
	{
		SetFontSize(25);
		DrawString(475, 10, "HP:", 0x0000ff, 0);

		for (int i = 0; i < mPlayer.hp; i++) {
			DrawGraph(515 + i * 25, 5, mImageHp, TRUE);
		}
	}

}

/***********************************************
 * �Q�[���I�[�o�[����
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void GameOver(void)
{
	const char* str2 = "---- X�L�[�������ă^�C�g���֖߂� ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2)				//x�L�[��������Ă�����
	{
		SceneMgr_ChangeScene(eScene_Menu);	//���j���[��ʂɈڍs
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(140, 220, "�f�`�l�d �n�u�d�q", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}

/***********************************************
 * �Q�[���t�B�j�b�V������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void GameFinish()
{

	const char* str2 = "---- X�L�[�������ă^�C�g���֖߂� ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2)				//x�L�[��������Ă�����
	{
		SceneMgr_ChangeScene(eScene_Menu);	//���j���[��ʂɈڍs
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(180, 220, "F I N I S H ! !", 0xff0000, 0);

	SetFontSize(20);
	DrawString(140, 440, str3, 0xff0000, 0);
}


/***********************************************
 * ���Ԑ���
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void GameTime()
{
	Seigen = (30000 - (GetNowCount() - StartTime)) / 1000;

	if (Seigen > 0)
	{
		SetFontSize(25);
		DrawFormatString(250, 10, GetColor(255, 0, 0), "�c��:%d�b", Seigen);
	}
	else
	{
		mgameStatus = false;

	}
}

/***********************************************
 * �Q�[�����Ԏ擾
 * ���@���F�Ȃ�
 * �߂�l�FmGameTime
 ***********************************************/
int Game_GetmGameTime()
{
	return mGameTime;
}

/***********************************************
 * �Q�[���󋵃Z�b�g
 * ���@���Fflg
 * �߂�l�FmGameTime
 ***********************************************/
void Game_SetmgameStatus(int flg)
{
	mgameStatus = flg;
}
