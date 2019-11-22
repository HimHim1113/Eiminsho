#include "CharMenu.h"
#include <DxLib.h>
#include "Define.h"
#include "Pad.h"


CharMenu::CharMenu()
{
	char_img[0] = LoadGraph("./dat/img/char/shibuki/big1.png");
	char_img[1] = LoadGraph("./dat/img/char/shibuki/big1.png");
	char_img[2] = LoadGraph("./dat/img/char/shibuki/big1.png");
}

void CharMenu::select() {
	if (Pad::getIns()->get(ePad::up) == 1 && num > 0) num--;
	else if (Pad::getIns()->get(ePad::down) == 1 && num < Player::CHAR_NUM - 1) num++;
	const char name[Player::CHAR_NUM][WORD_MAX] = { "ホーミングショット", "フォーワードショット", "ワイドショット" };
	DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, 1.0, 0.0, char_img[num], TRUE);
	for (int i = 0; i < Player::CHAR_NUM; i++) {
		int col = i == num ? 255 : 100;
		DrawStringToHandle(200 + 50 * i, 200 + 100 * i, name[i], GetColor(col, col, col), font);
	}
}