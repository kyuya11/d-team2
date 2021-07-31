#include "Help.h"
#include "Scene.h"
#include "DxLib.h"
#include "Input.h"

static int mImageHandle;	//�摜�i�[�p�ϐ�
static int WaitTime;		//�҂�����

/***********************************************
 * �w���v ������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Initialize() {
	mImageHandle = LoadGraph("images/haikei3.png");	//�摜�̃��[�h
	WaitTime = 0;	//�҂����ԏ�����
}


/***********************************************
 * �w���v �I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Finalize() {
	DeleteGraph(mImageHandle);	//�摜�̉��
}


/***********************************************
 * �w���v �X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {	//Y�{�^����ESC�L�[��
		SceneMgr_ChangeScene(eScene_Menu);	//�V�[�������j���[�Ɉڍs
	}
}


/***********************************************
 * �w���v �`��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);	//�Q�[���w�i�`��

	SetFontSize(30);

	DrawString(100, 150, "�E���A�E�L�[�ňړ��B����", GetColor(0, 0, 255));
	DrawString(100, 200, "�E��L�[�ŃW�����v�B��", GetColor(0, 0, 255));
	DrawString(100, 250, "�E���ԓ��̊Ԃ͓G������܂��낤�B", GetColor(255, 0, 0));
	DrawString(100, 300, "�EHP��0�ɂȂ�ƃQ�[���I�[�o�[!", GetColor(255, 0, 0));


	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "Esc�L�[�܂���B�{�^���������ƃ��j���[��ʂɖ߂�܂��B",
			GetColor(0, 0, 0));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}