#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <math.h>

/*************************
** �v���g�^�C�v�錾 **
*************************/
int HitCircleEnemy(PLAYER*, ENEMY*);	//�G�̓����蔻��


struct ENEMY mEnemy[ENEMY_MAX];			//�G�l�~�[�\��
static int mImageEnemyKatatumuri;		//�J�^�c�����̉摜������ϐ�
static int mImageEnemyKatatumuri_gyaku;	//�J�^�c�����̋t�����̉摜������ϐ�
static int mImageEnemyKaeru;			//�J�G���̉摜������ϐ�
static int mImageEnemyKaeru_gyaku;		//�J�G���̋t�����̉摜������ϐ�
static int mImageEnemyGa;				//��̉摜������ϐ�
static int mImageEnemyGa_gyaku;			//��̋t�����̉摜������ϐ�
static int mSoundsDamage;				//�_���[�W���󂯂����̉���������ϐ�


/***********************************************
 * �G ������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Initialize()
{
	mImageEnemyKatatumuri = LoadGraph("images/katatumuri3.png");			//�摜�̃��[�h
	mImageEnemyKatatumuri_gyaku = LoadGraph("images/katatumuri_gyaku.png");	//�摜�̃��[�h
	mImageEnemyKaeru = LoadGraph("images/kaeru6.png");						//�摜�̃��[�h
	mImageEnemyKaeru_gyaku = LoadGraph("images/kaeru8.png");				//�摜�̃��[�h
	mImageEnemyGa = LoadGraph("images/ga2.png");							//�摜�̃��[�h
	mImageEnemyGa_gyaku = LoadGraph("images/ga4.png");						//�摜�̃��[�h

	mSoundsDamage = LoadSoundMem("sounds/damage.mp3");						//�����t�@�C���̃��[�h

	for (int i = 0; i < ENEMY_MAX; i++) //�G�l�~�[�t���O�̏�����
	{
		mEnemy[i].flg = FALSE;
	}
}

/***********************************************
 * �G �I���X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Finalize()
{

	DeleteGraph(mImageEnemyKaeru);			//�摜�̉��
	DeleteGraph(mImageEnemyKaeru_gyaku);	//�摜�̉��

	DeleteGraph(mImageEnemyKatatumuri);		//�摜�̉��
	DeleteGraph(mImageEnemyKatatumuri_gyaku);//�摜�̉��

	DeleteGraph(mImageEnemyGa);				//�摜�̉��
	DeleteGraph(mImageEnemyGa_gyaku);		//�摜�̉��

}

/***********************************************
 * �G �����X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Update()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == TRUE)
		{

			mEnemy[i].x += mEnemy[i].mx;	//�����W�ɑ΂���ړ���
			mEnemy[i].y += mEnemy[i].my;	//y���W�ɑ΂���ړ���

			mEnemy[i].cnt++;				//�G���łĂ��Ă���̃J�E���g

			switch (mEnemy[i].type)
			{
			case 1: EnemyType01(&mEnemy[i]); break;	//�J�^�c�����̍s���p�^�[��
			case 2: EnemyType02(&mEnemy[i]); break;	//�J�^�c�����̍s���p�^�[��
			case 3: EnemyType03(&mEnemy[i]); break;	//�J�G���̍s���p�^�[��
			case 4: EnemyType04(&mEnemy[i]); break; //�J�G���̍s���p�^�[��
			case 5: EnemyType05(&mEnemy[i]); break;	//��̍s���p�^�[��
			case 6: EnemyType06(&mEnemy[i]); break;	//��̍s���p�^�[��
			}

			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {
				mEnemy[i].y = 370;	//�n�ʂ̍���
			}
			if (mEnemy[i].x > SCREEN_WIDTH + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;	//�E�[�𒴂��������
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;	//���[�𒴂��������
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE)
			{
				if (mPlayer.flg == true)
				{
					mPlayer.hp -= 1;		//�v���C���[�̗̑͂����炷
					mPlayer.flg = FALSE;	//�v���C���[�̓����蔻����ꎞ�I�ɏ���
					mPlayer.count = 0;		//�v���C���[�̃J�E���g��0�ɂ���
					mEnemy[i].flg = FALSE;	//�G������
					PlaySoundMem(mSoundsDamage, DX_PLAYTYPE_BACK);//�v���C���[���G�ɓ����������̉����v���C
				}
			}
		}
	}
}

/***********************************************
 * �G �`�揈��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == TRUE)
		{
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);	//�摜����]�A�g�又��
		}
	}

}

//�G�̃X�e�[�^�X������
int CreateEnemy(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == FALSE)
		{
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;

			//�J�^�c����
			if (type == 1 || type == 2)
			{
				mEnemy[i].img = mImageEnemyKatatumuri;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			//�J�G��
			if (type == 3 || type == 4)
			{
				mEnemy[i].img = mImageEnemyKaeru;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			//��
			if (type == 5 || type == 6)
			{
				mEnemy[i].img = mImageEnemyGa;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			mEnemy[i].x = x;		//�G�̂����W
			mEnemy[i].y = y;		//�G��y���W
			mEnemy[i].w = w;		//�G�̉���
			mEnemy[i].h = h;		//�G�̍���
			mEnemy[i].mx = mx;		//�G�̂��̈ړ���
			mEnemy[i].my = my;		//�G�̂��̈ړ���
			mEnemy[i].cnt = 0;		//�G�̏o�����Ă���̃J�E���g������
			mEnemy[i].yadd2 = 0.0f;	//�G�̃W�����v�͂̏�����


			return TRUE;
		}
	}

	return FALSE;
}

/*
�J�^�c�����F�E����o�Ă��Đ^�������s���č��[�𒴂����������
*/
void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->x == 0) //�G��x���W��0�ɂȂ�����
	{
		mEnemy->mx = 1;		//���ւ̈ړ��ʂ�1�ɂ���
	}

}

/*
�J�^�c�����F������o�Ă��Đ^�������s���ĉE�[�𒴂����������
*/
void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->x == 1)	//�G�̍��W��1�ɂȂ�����
	{
		mEnemy->img = mImageEnemyKatatumuri_gyaku;	//�t�����̉摜�ɂ���
	}
}

/*
�J�G���F�E���璵�˂Ȃ���łĂ��č��[�𒴂����������
*/
void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) //�G�̂����W��370�ɂȂ�����
	{
		mEnemy->yadd2 = -5.0f;	//�W�����v����
	}
	mEnemy->y += mEnemy->yadd2;	//y���W��yadd2�̒l�����Z
	mEnemy->yadd2 += 0.2f;		//0.2f�����Z����

}

/*
�J�G���F�����璵�˂Ȃ���łĂ��ĉE�[�𒴂����������
*/
void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) //�G�̂����W��370�ɂȂ�����
	{
		mEnemy->yadd2 = -5.0f;	//�W�����v����
	}
	mEnemy->y += mEnemy->yadd2;	//y���W��yadd2�̒l�����Z
	mEnemy->yadd2 += 0.2f;		//0.2f�����Z����

	if (mEnemy->x == 1)			//�G��x���W��1�ɂȂ�����
	{
		mEnemy->img = mImageEnemyKaeru_gyaku;	//�t�����̉摜�ɂ���
	}

}

/*
��F�E����o�Ă��č��Ƀt���t����тȂ��獶�[�𒴂����������
*/
void EnemyType05(ENEMY* mEnemy)
{

	if (mEnemy->cnt % 20 == 0)	//�G���o�����Ă���̃J�E���g��20�Ŋ������]�肪0�Ȃ�
	{
		mEnemy->my = 1;			//�G��y���ւ̈ړ��ʂ�1�ɂ���
	}
	if (mEnemy->cnt % 40 == 0)	//�G���o�����Ă���̃J�E���g��40�Ŋ������]�肪0�Ȃ�
	{
		{
			mEnemy->my = -1;		//�G��y���ւ̈ړ��ʂ�-1�ɂ���
		}
	}
}
	/*
	��F������o�Ă��ĉE�Ƀt���t����тȂ���E�[�𒴂����������
	*/
void EnemyType06(ENEMY* mEnemy)
{
	if (mEnemy->x == 1)						//�G��x���W��1�Ȃ�
	{
		mEnemy->img = mImageEnemyGa_gyaku;	//�t�����̉摜�ɂ���
	}

	if (mEnemy->cnt % 20 == 0)				//�G���o�����Ă���̃J�E���g��20�Ŋ������]�肪0�Ȃ�
	{
		mEnemy->my = 1;						//�G��y���ւ̈ړ��ʂ�1�ɂ���
	}
	if (mEnemy->cnt % 40 == 0)				//�G���o�����Ă���̃J�E���g��40�Ŋ������]�肪0�Ȃ� 
	{
		mEnemy->my = -1;					//�G��y���ւ̈ړ��ʂ�-1�ɂ���
	}
}

	/**********************************
	 * �����蔻��i�~�j
	 * ���@���FPLAYER�|�C���^, ENEMY�|�C���^
	 * �߂�l�FTRUE:������, FALSE:�Ȃ�
	 **********************************/
int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}




