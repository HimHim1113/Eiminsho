#include "Board.h"
#include <DxLib.h>
#include "Define.h"


Board::Board() {
	/*
	img_board[10] = LoadGraph("../dat/img/board/10.png");
	img_board[11] = LoadGraph("../dat/img/board/11.png");
	img_board[12] = LoadGraph("../dat/img/board/12.png");
	*/
	img_board[20] = LoadGraph("./dat/img/board/20.png");
	font = CreateFontToHandle("ÉÅÉCÉäÉI", 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
}

bool Board::main(int zanki, int bomb, int graze, int level)
{
	draw(zanki, bomb, graze, level);
	drawFrame();
    return true;
}

void Board::draw(int zanki, int bomb, int graze, int level) const
{
	/*
	DrawGraph(0, 0, img_board[10], FALSE);
	DrawGraph(0, 16, img_board[11], FALSE);
	DrawGraph(0, 464, img_board[12], FALSE);
	*/
	DrawGraph(Define::OUT_W, 0, img_board[20], FALSE);
	DrawStringToHandle(Define::OUT_W + 50, 150, "Player", GetColor(255, 255, 255), font);
	DrawStringToHandle(Define::OUT_W + 50, 200, "Bomb", GetColor(255, 255, 255), font);
	for (int i = 0; i < zanki; i++) DrawString(Define::OUT_W + 170 + i * 20, 160, "Åú", GetColor(230, 10, 10));
	for (int i = 0; i < bomb; i++) DrawString(Define::OUT_W + 170 + i * 20, 210, "Åú", GetColor(10, 10, 230));
	DrawFormatStringToHandle(Define::OUT_W + 50, 250, GetColor(255, 255, 255), font, "Graze %4d", graze);
	DrawStringToHandle(Define::OUT_W + 50, 350, (level == 0 ? "Easy" : (level == 1 ? "Normal" : "Hard")), GetColor(255, 255, 255), font);
}

void Board::drawFrame() const
{
    int color = GetColor(0, 64, 128);
    const int x = Define::IN_X;
    const int y = Define::IN_Y;
    const int w = Define::IN_W;
    const int h = Define::IN_H;
    DrawLine(x,     y,     x + w, y,     color);
    DrawLine(x,     y,     x,     y + h, color);
    DrawLine(x + w, y,     x + w, y + h, color);
    DrawLine(x,     y + h, x + w, y + h, color);
}
