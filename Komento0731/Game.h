#pragma once

#define PI 3.1415926535897932384626433832795f

void Game_Initialize();	//������
void Game_Finalize();	//�I������
void Game_Update();		//�X�V
void Game_Draw();		//�`��

void GameOver(void);	//�Q�[���I�[�o�[����
void GameFinish();		//�Q�[���t�B�j�b�V������
void GameTime();		//�Q�[���o�ߎ���

int Game_GetmGameTime();	  //�Q�[�����Ԏ擾
void Game_SetmgameStatus(int);//�Q�[���󋵃Z�b�g
