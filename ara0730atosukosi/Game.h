#pragma once

#define PI 3.1415926535897932384626433832795f

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();

//void BackScroll();
void GameOver(void);
void GameFinish();
void GameTime();

int Game_GetmGameTime();
void Game_SetmgameStatus(int);
