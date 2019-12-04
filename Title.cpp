#include "Title.h"
#include <DxLib.h>


Title::Title()
{
	font = CreateFontToHandle("ÉÅÉCÉäÉI", 80, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	img = LoadGraph("./dat/img/back/menu/narabi.png");
}

void Title::main() {
	DrawGraph(0, 0, img, FALSE);
	DrawStringToHandle(300, 200, "êÛòQâiñ∞è¥", GetColor(255, 255, 255), font);
	DrawStringToHandle(300, 400, "Press Z", GetColor(255, 255, 255), font);
}
