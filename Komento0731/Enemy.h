#pragma once

#define PI 3.1415926535897932384626433832795f

const int ENEMY_MAX = 9;		//�G�̍ő吔
const int ENEMY_IMAGE_MAX = 3;	//�G�̉摜�̍ő吔


const int ENEMY_ZAKO_HIT_R = 9;	//�G�̓����蔻��

//�G�l�~�[�\����
struct ENEMY {
	bool flg;		//�G�����邩���Ȃ��̊Ǘ�
	int type;		//�G�̎�ނ̊Ǘ�
	int img;		//�G�̉摜�̊Ǘ�
	int x, y, w, h;	//�G��x���W�Ay���W�A�����A�����̊Ǘ�
	int mx, my;		//�G��x���ɑ΂��Ă̈ړ��ʁAy���ɑ΂��Ă̈ړ��ʂ̊Ǘ�
	int cnt;		//�G���o�����Ă���̃J�E���g�̊Ǘ�
	int r;			//�G�̔��a�̊Ǘ�
	float yadd2;	//�G�̃W�����v�͂̊Ǘ�
};

extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();	//������
extern void Enemy_Finalize();	//�I������
extern void Enemy_Update();		//�X�V
extern void Enemy_Draw();		//�`��

int CreateEnemy(int, int, int, int, int, int, int, int);	//�G�̍\��

void EnemyType01(ENEMY*);	//�G�l�~�[�^�C�v01�̈ړ�
void EnemyType02(ENEMY*);	//�G�l�~�[�^�C�v02�̈ړ�
void EnemyType03(ENEMY*);	//�G�l�~�[�^�C�v03�̈ړ�
void EnemyType04(ENEMY*);	//�G�l�~�[�^�C�v04�̈ړ�
void EnemyType05(ENEMY*);	//�G�l�~�[�^�C�v05�̈ړ�
void EnemyType06(ENEMY*);	//�G�l�~�[�^�C�v06�̈ړ�
