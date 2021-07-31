#include "End.h"
#include "Scene.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int StopTime;	//���Ԑ���

//������
void End_Initialize() {
	mImageHandle = LoadGraph("images/End.png");//�摜�̃��[�h
	StopTime = 0;		//���Ԑ����̏�����
}

//�I������
void End_Finalize() {
	DeleteGraph(mImageHandle);//�摜�̉��
}


//�`��
void End_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);	//�摜��`��

	SetFontSize(25);
	DrawString(340, 456, "Thank you for Playing", 0xff0000, 0);

	//�^�C���̉��Z�������I�� (�Q�b��)
	if (++StopTime > 120) {
		SceneMgr_ChangeScene(eScene_Stop); //�V�[�����Q�[����ʂɕύX
	}
}