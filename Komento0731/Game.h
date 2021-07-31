#pragma once

#define PI 3.1415926535897932384626433832795f

void Game_Initialize();	//初期化
void Game_Finalize();	//終了処理
void Game_Update();		//更新
void Game_Draw();		//描画

void GameOver(void);	//ゲームオーバー処理
void GameFinish();		//ゲームフィニッシュ処理
void GameTime();		//ゲーム経過時間

int Game_GetmGameTime();	  //ゲーム時間取得
void Game_SetmgameStatus(int);//ゲーム状況セット
