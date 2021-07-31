#include "DxLib.h"
#include "Scene.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <math.h>

/*************************
** プロトタイプ宣言 **
*************************/
int HitCircleEnemy(PLAYER*, ENEMY*);	//敵の当たり判定


struct ENEMY mEnemy[ENEMY_MAX];			//エネミー構造
static int mImageEnemyKatatumuri;		//カタツムリの画像を入れる変数
static int mImageEnemyKatatumuri_gyaku;	//カタツムリの逆向きの画像を入れる変数
static int mImageEnemyKaeru;			//カエルの画像を入れる変数
static int mImageEnemyKaeru_gyaku;		//カエルの逆向きの画像を入れる変数
static int mImageEnemyGa;				//蛾の画像を入れる変数
static int mImageEnemyGa_gyaku;			//蛾の逆向きの画像を入れる変数
static int mSoundsDamage;				//ダメージを受けた時の音声を入れる変数


/***********************************************
 * 敵 初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Enemy_Initialize()
{
	mImageEnemyKatatumuri = LoadGraph("images/katatumuri3.png");			//画像のロード
	mImageEnemyKatatumuri_gyaku = LoadGraph("images/katatumuri_gyaku.png");	//画像のロード
	mImageEnemyKaeru = LoadGraph("images/kaeru6.png");						//画像のロード
	mImageEnemyKaeru_gyaku = LoadGraph("images/kaeru8.png");				//画像のロード
	mImageEnemyGa = LoadGraph("images/ga2.png");							//画像のロード
	mImageEnemyGa_gyaku = LoadGraph("images/ga4.png");						//画像のロード

	mSoundsDamage = LoadSoundMem("sounds/damage.mp3");						//音声ファイルのロード

	for (int i = 0; i < ENEMY_MAX; i++) //エネミーフラグの初期化
	{
		mEnemy[i].flg = FALSE;
	}
}

/***********************************************
 * 敵 終了更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Enemy_Finalize()
{

	DeleteGraph(mImageEnemyKaeru);			//画像の解放
	DeleteGraph(mImageEnemyKaeru_gyaku);	//画像の解放

	DeleteGraph(mImageEnemyKatatumuri);		//画像の解放
	DeleteGraph(mImageEnemyKatatumuri_gyaku);//画像の解放

	DeleteGraph(mImageEnemyGa);				//画像の解放
	DeleteGraph(mImageEnemyGa_gyaku);		//画像の解放

}

/***********************************************
 * 敵 処理更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Enemy_Update()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == TRUE)
		{

			mEnemy[i].x += mEnemy[i].mx;	//ｘ座標に対する移動量
			mEnemy[i].y += mEnemy[i].my;	//y座標に対する移動量

			mEnemy[i].cnt++;				//敵がでてきてからのカウント

			switch (mEnemy[i].type)
			{
			case 1: EnemyType01(&mEnemy[i]); break;	//カタツムリの行動パターン
			case 2: EnemyType02(&mEnemy[i]); break;	//カタツムリの行動パターン
			case 3: EnemyType03(&mEnemy[i]); break;	//カエルの行動パターン
			case 4: EnemyType04(&mEnemy[i]); break; //カエルの行動パターン
			case 5: EnemyType05(&mEnemy[i]); break;	//蛾の行動パターン
			case 6: EnemyType06(&mEnemy[i]); break;	//蛾の行動パターン
			}

			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {
				mEnemy[i].y = 370;	//地面の高さ
			}
			if (mEnemy[i].x > SCREEN_WIDTH + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;	//右端を超えたら消去
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;	//左端を超えたら消去
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE)
			{
				if (mPlayer.flg == true)
				{
					mPlayer.hp -= 1;		//プレイヤーの体力を減らす
					mPlayer.flg = FALSE;	//プレイヤーの当たり判定を一時的に消す
					mPlayer.count = 0;		//プレイヤーのカウントを0にする
					mEnemy[i].flg = FALSE;	//敵を消す
					PlaySoundMem(mSoundsDamage, DX_PLAYTYPE_BACK);//プレイヤーが敵に当たった時の音声プレイ
				}
			}
		}
	}
}

/***********************************************
 * 敵 描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == TRUE)
		{
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);	//画像を回転、拡大処理
		}
	}

}

//敵のステータス初期化
int CreateEnemy(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (mEnemy[i].flg == FALSE)
		{
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;

			//カタツムリ
			if (type == 1 || type == 2)
			{
				mEnemy[i].img = mImageEnemyKatatumuri;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			//カエル
			if (type == 3 || type == 4)
			{
				mEnemy[i].img = mImageEnemyKaeru;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			//蛾
			if (type == 5 || type == 6)
			{
				mEnemy[i].img = mImageEnemyGa;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			mEnemy[i].x = x;		//敵のｘ座標
			mEnemy[i].y = y;		//敵のy座標
			mEnemy[i].w = w;		//敵の横幅
			mEnemy[i].h = h;		//敵の高さ
			mEnemy[i].mx = mx;		//敵のｘの移動量
			mEnemy[i].my = my;		//敵のｙの移動量
			mEnemy[i].cnt = 0;		//敵の出現してからのカウント初期化
			mEnemy[i].yadd2 = 0.0f;	//敵のジャンプ力の初期化


			return TRUE;
		}
	}

	return FALSE;
}

/*
カタツムリ：右から出てきて真っすぐ行って左端を超えたら消える
*/
void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->x == 0) //敵のx座標が0になったら
	{
		mEnemy->mx = 1;		//ｘへの移動量を1にする
	}

}

/*
カタツムリ：左から出てきて真っすぐ行って右端を超えたら消える
*/
void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->x == 1)	//敵の座標が1になったら
	{
		mEnemy->img = mImageEnemyKatatumuri_gyaku;	//逆向きの画像にする
	}
}

/*
カエル：右から跳ねながらでてきて左端を超えたら消える
*/
void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) //敵のｙ座標が370になったら
	{
		mEnemy->yadd2 = -5.0f;	//ジャンプする
	}
	mEnemy->y += mEnemy->yadd2;	//y座標にyadd2の値を加算
	mEnemy->yadd2 += 0.2f;		//0.2fずつ加算する

}

/*
カエル：左から跳ねながらでてきて右端を超えたら消える
*/
void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->y == 370) //敵のｙ座標が370になったら
	{
		mEnemy->yadd2 = -5.0f;	//ジャンプする
	}
	mEnemy->y += mEnemy->yadd2;	//y座標にyadd2の値を加算
	mEnemy->yadd2 += 0.2f;		//0.2fずつ加算する

	if (mEnemy->x == 1)			//敵のx座標が1になったら
	{
		mEnemy->img = mImageEnemyKaeru_gyaku;	//逆向きの画像にする
	}

}

/*
蛾：右から出てきて左にフラフラ飛びながら左端を超えたら消える
*/
void EnemyType05(ENEMY* mEnemy)
{

	if (mEnemy->cnt % 20 == 0)	//敵が出現してからのカウントを20で割った余りが0なら
	{
		mEnemy->my = 1;			//敵のy軸への移動量を1にする
	}
	if (mEnemy->cnt % 40 == 0)	//敵が出現してからのカウントを40で割った余りが0なら
	{
		{
			mEnemy->my = -1;		//敵のy軸への移動量を-1にする
		}
	}
}
	/*
	蛾：左から出てきて右にフラフラ飛びながら右端を超えたら消える
	*/
void EnemyType06(ENEMY* mEnemy)
{
	if (mEnemy->x == 1)						//敵のx座標が1なら
	{
		mEnemy->img = mImageEnemyGa_gyaku;	//逆向きの画像にする
	}

	if (mEnemy->cnt % 20 == 0)				//敵が出現してからのカウントを20で割った余りが0なら
	{
		mEnemy->my = 1;						//敵のy軸への移動量を1にする
	}
	if (mEnemy->cnt % 40 == 0)				//敵が出現してからのカウントを40で割った余りが0なら 
	{
		mEnemy->my = -1;					//敵のy軸への移動量を-1にする
	}
}

	/**********************************
	 * 当たり判定（円）
	 * 引　数：PLAYERポインタ, ENEMYポインタ
	 * 戻り値：TRUE:当たり, FALSE:なし
	 **********************************/
int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}




