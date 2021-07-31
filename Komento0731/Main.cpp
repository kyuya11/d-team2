#include "DxLib.h"
#include "Scene.h"
#include "Input.h"




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�^�C�g����ݒ�A�E�B���h�E���[�h�ύX�ADX���C�u�����������A����ʐݒ�
	SetMainWindowText("YOKERO"), ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	
	SceneMgr_Initialize();	//������

	while (ProcessMessage() == 0) {	//���b�Z�[�W����

		if (SceneMgr_GameEnd_Status()) {
			break;	//���j���[����I����I��
		}

		ClearDrawScreen();	//��ʏ���

		InputKey();			//����
		
		SceneMgr_Update();	//�X�V
		SceneMgr_Draw();	//�`��


		ScreenFlip();		//��ʍX�V

	}
	SceneMgr_Finalize();


	DxLib_End();	//DX���C�u�����I������
	return 0;
}