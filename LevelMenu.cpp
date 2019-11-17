#include "LevelMenu.h"
#include <DxLib.h>
#include "Pad.h"


void LevelMenu::select() {
	if (Pad::getIns()->get(ePad::left) == 1 && num > 0) num--;
	else if (Pad::getIns()->get(ePad::right) == 1 && num < NAME_MAX - 1) num++;
	const char name[NAME_MAX][WORD_MAX] = { "Easy", "Normal", "Hard" };
	for (int i = 0; i < NAME_MAX; i++) {
		int col = i == num ? 255 : 150;
		DrawStringToHandle(200 * i + 100, 100, name[i], GetColor(col, col, col), font);
	}
}
