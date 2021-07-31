#include "DxLib.h"
#include "Scene.h"
#include "Menu.h"
#include "Input.h"

static int mImageHandle;  //�摜�n���h���i�[�p�ϐ�
static int mImageSelect;  //�摜�n���h���i�[�p�ϐ�
static int MenuNumber = 0;  //���j���[�J�[�\���Ǘ��p�ϐ�

static int mSoundsSelect;  //���t�@�C���i�[�p�ϐ�
static int mSoundsMove;    //���t�@�C���i�[�p�ϐ�



/***********************************************
 * ���j���[�@������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Menu_Initialize()
{
	mImageHandle = LoadGraph("images/title.png");			//�摜�̃��[�h
	mImageSelect = LoadGraph("images/select.png");			//�摜�̃��[�h

	mSoundsSelect = LoadSoundMem("sounds/kettei.mp3");		//���艹�̃��[�h
	mSoundsMove = LoadSoundMem("sounds/select.mp3");		//�I�����̃��[�h
	PlayMusic("sounds/kouhoBGM3.mp3", DX_PLAYTYPE_LOOP);	//BGM�Đ�
}


/***********************************************
 * ���j���[�@�I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Menu_Finalize()
{
	DeleteGraph(mImageHandle);		//�摜�̉��
	DeleteGraph(mImageSelect);		//�摜�̉��

	StopSoundMem(mSoundsSelect);	//�摜�̉��
	StopSoundMem(mSoundsMove);		//�摜�̉��

	StopMusic();					//BGM��~

}


/***********************************************
 * ���j���[�@�X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Menu_Update()
{
	//���j���[�J�[�\���ړ�����
	if (iKeyFlg & PAD_INPUT_DOWN)
	{
		PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
		if (++MenuNumber > 2) MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP)
	{
		PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
		if (--MenuNumber < 0) MenuNumber = 2;
	}

	if (iKeyFlg == PAD_INPUT_1)	//Z�L�[��������Ă�����
	{
		PlaySoundMem(mSoundsSelect, DX_PLAYTYPE_BACK);
		WaitTimer(500);
		switch (MenuNumber) {		//�V�[���ɂ���ď����𕪊�
		case 0:
			SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_Help); //�V�[�����Q�[����ʂɕύX
			break;
		case 2:
			SceneMgr_ChangeScene(eScene_End); //�V�[�����Q�[����ʂɕύX
			break;

		}
	}

}


/***********************************************
 * ���j���[�@�`��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Menu_Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);

	// ���j���[�J�[�\��
	DrawRotaGraph(240, 187 + MenuNumber * 61, 1.0f, 1.0f, mImageSelect, TRUE);

}
