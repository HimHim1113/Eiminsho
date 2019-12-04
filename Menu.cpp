#include "Menu.h"
#include <DxLib.h>
#include "Pad.h"
#include "Keyboard.h"


void Menu::select() {
	if (Pad::getIns()->get(ePad::bom) == 1 || Pad::getIns()->get(ePad::start) == 1) num = NAME_MAX - 1;
	else if (Pad::getIns()->get(ePad::up) == 1 && num > 0) num--;
	else if (Pad::getIns()->get(ePad::down) == 1 && num < NAME_MAX - 1) num++;
	DrawGraph(0, 0, img, FALSE);
	const char name[NAME_MAX][WORD_MAX] = { "Play", "Dice", "Help", "Quit" };
	for (int i = 0; i < NAME_MAX; i++) {
		int col = i == num ? 255 : 150;
		DrawStringToHandle(i * 25 + 100, i * 100 + 100, name[i], GetColor(col, col, col), font);
	}
	if (dice > 0) DrawFormatStringToHandle(300, 200, GetColor(255, 255, 255), font, "%d", dice);
}
