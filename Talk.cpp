#include "Talk.h"
#include <DxLib.h>
#include <cstdlib>
#include <cstring>
#include "Define.h"
#include "Pad.h"
#include "Keyboard.h"


Talk::Talk() :
	ishuman(-1),
	str("\0")
{
	font = CreateFontToHandle("‚l‚r ƒSƒVƒbƒN", 20, 2, DX_FONTTYPE_ANTIALIASING_EDGE);

	char_pic[0] = LoadGraph("./dat/img/char/hibiki/hibiki0.png");
	char_pic[1] = LoadGraph("./dat/img/char/hibiki/hibiki1.png");
	char_pic[2] = LoadGraph("./dat/img/char/hibiki/hibiki2.png");
	char_pic[3] = LoadGraph("./dat/img/char/hibiki/hibiki3.png");
	enemy_pic[0] = LoadGraph("./dat/img/char/hibiki/hibiki0.png");
	enemy_pic[1] = LoadGraph("./dat/img/char/hibiki/hibiki1.png");
	enemy_pic[2] = LoadGraph("./dat/img/char/hibiki/hibiki2.png");
	enemy_pic[3] = LoadGraph("./dat/img/char/hibiki/hibiki3.png");
}

int Talk::main() {
	if (flag > 0) {
		if (Pad::getIns()->get(ePad::shot) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) % 5 == 1) {
			FileRead_scanf(fp, "%d,%d,", &ishuman, &face);
			FileRead_gets(str, 100 - 1, fp);
		}
		if (ishuman <= 0) flag = 0;
		draw();
	}
	return 0;
}

void Talk::draw() {
	if(ishuman == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawTurnGraph(Define::CENTER_X - 350, 200, char_pic[face], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(Define::CENTER_X + 50, 200, enemy_pic[face], TRUE);
		DrawStringToHandle(200, 600, str, GetColor(255, 100, 100), font);
	}
	else if (ishuman == 2) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(Define::CENTER_X + 50, 200, enemy_pic[face], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawTurnGraph(Define::CENTER_X - 350, 200, char_pic[face], TRUE);
		DrawStringToHandle(200, 600, str, GetColor(100, 100, 255), font);
	}
	else if (ishuman == 3) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Talk::ini(int spell) {
	if (spell == 0) flag = 1;
	else flag = 0;
	ishuman = -1;
	switch (-1) {
	case 0:
		fp = FileRead_open("./dat/text/hibiki.txt");
		break;
	case 1:
		fp = FileRead_open("./dat/text/ayakashi.txt");
		break;
	case 2:
		fp = FileRead_open("./dat/text/midori.txt");
		break;
	default:
		flag = 0;
		break;
	}
}

void Talk::fin() {
	FileRead_close(fp);
}