#include "Back01.h"
#include "Define.h"
#include <DxLib.h>

using namespace std;

const static int   IMG_WIDTH = 700;
const static float SCROLL_SPEED = 2.0f;

Back01::Back01() :
	exrate(1.0),
	num(-1),
	count(-1)
{
    img_first = LoadGraph("./dat/img/back/normal/katakana.png");
	img_second = LoadGraph("./dat/img/back/normal/shiki.png");
	img[0] = LoadGraph("./dat/img/back/normal/spring.png");
	img[1] = LoadGraph("./dat/img/back/normal/summer.png");
	img[2] = LoadGraph("./dat/img/back/normal/autumn.png");
	img[3] = LoadGraph("./dat/img/back/normal/winter.png");
	_list[0][0] = make_shared<Quadrangle>(IMG_WIDTH * 0.0f, 0.0f, LoadGraph("./dat/img/back/normal/spring.png"));
	_list[0][1] = make_shared<Quadrangle>(IMG_WIDTH * 1.0f, 0.0f, LoadGraph("./dat/img/back/normal/spring.png"));
	_list[1][0] = make_shared<Quadrangle>(IMG_WIDTH * 0.0f, 0.0f, LoadGraph("./dat/img/back/normal/summer.png"));
	_list[1][1] = make_shared<Quadrangle>(IMG_WIDTH * 1.0f, 0.0f, LoadGraph("./dat/img/back/normal/summer.png"));
	_list[2][0] = make_shared<Quadrangle>(IMG_WIDTH * 0.0f, 0.0f, LoadGraph("./dat/img/back/normal/autumn.png"));
	_list[2][1] = make_shared<Quadrangle>(IMG_WIDTH * 1.0f, 0.0f, LoadGraph("./dat/img/back/normal/autumn.png"));
	_list[3][0] = make_shared<Quadrangle>(IMG_WIDTH * 0.0f, 0.0f, LoadGraph("./dat/img/back/normal/winter.png"));
	_list[3][1] = make_shared<Quadrangle>(IMG_WIDTH * 1.0f, 0.0f, LoadGraph("./dat/img/back/normal/winter.png"));
}

void Back01::update(int change)
{
	if (change == 1) {
		count = 0;
		if (num == -2) num = -1;
		else if (num < MAX - 1) {
			num++;
			for (int i = 0; i < 2; i++) {
				_list[num][i]->x = (float)IMG_WIDTH * i - (IMG_WIDTH - Define::OUT_W) / 2.0f;
			}
		}
		else num = -2;
	}
	else if (change == -1) {
		count = -1;
		num = -1;
		exrate = 1.0;
	}
	if (count >= 0) {
		count++;
		if (count >= 240) {
			count = -1;
			exrate = 1.0;
		}
		if (count < 150) exrate = 0.0;
		else {
			exrate = (count - 150) / 60.0;
			if (exrate > 1.0) exrate = 1.0;
		}
	}
	if (num >= 0 && count < 0) update();
}

bool Back01::update() 
{
	for (int i = 0; i < 2; i++) {//全て上にスクロールさせる
		_list[num][i]->x -= SCROLL_SPEED;
		if (_list[num][i]->x < -IMG_WIDTH) {//上に行き切ったら
			_list[num][i]->x += IMG_WIDTH * 2.0f;//一番下に下げる
		}
	}
    return true;
}

void Back01::draw() const
{
    SetDrawMode(DX_DRAWMODE_BILINEAR);
	if (count >= 0) {
		if(num >= 0) DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, exrate, 0.0, img[num], FALSE);
		else if(num == -2) DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, exrate, 0.0, img_second, FALSE);
		else DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, exrate, 0.0, img_first, FALSE);
	}
	else {
		if (num >= 0) {
			DrawGraphF(_list[num][0]->x, _list[num][0]->y, _list[num][0]->img, FALSE);
			DrawTurnGraphF(_list[num][1]->x, _list[num][1]->y, _list[num][1]->img, FALSE);
		}
		else if(num == -2) DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, 1.0, 0.0, img_second, FALSE);
		else DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, 1.0, 0.0, img_first, FALSE);
	}
	
    SetDrawMode(DX_DRAWMODE_NEAREST);
}
