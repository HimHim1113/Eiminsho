#include "LevelMenu.h"
#include <DxLib.h>
#include "Pad.h"


LevelMenu::LevelMenu() :
	explain
{
	"高専生ならできてほしい",
	"これができれば一人前",
	"ノーミスでできたらすごい"
}
{
	img = LoadGraph("./dat/img/back/menu/katakana.png");
}

void LevelMenu::select() {
	if ((Pad::getIns()->get(ePad::up) == 1 || Pad::getIns()->get(ePad::left) == 1) && num > 0) num--;
	else if ((Pad::getIns()->get(ePad::down) == 1 || Pad::getIns()->get(ePad::right) == 1) && num < NAME_MAX - 1) num++;
	DrawGraph(0, 0, img, FALSE);
	const char name[NAME_MAX][WORD_MAX] = { "Easy", "Normal", "Hard" };
	for (int i = 0; i < NAME_MAX; i++) {
		int col = i == num ? 255 : 150;
		DrawStringToHandle(100 + i * 300, 100 + i * 25, name[i], GetColor(col, col, col), font);
	}
	DrawStringToHandle(100, 400, explain[num], GetColor(255, 255, 255), font);
}
