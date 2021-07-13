#include "DxLib.h"

int iOldKey; 
int iNowKey; 
int iKeyFlg; 

void InputKey(void) 
{

	iOldKey = iNowKey;
	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	iKeyFlg = iNowKey & ~iOldKey;

}