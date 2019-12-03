#include "Texture.h"
#include <DxLib.h>
#include "Define.h"


Texture::Texture() :
	count(0)
{
	tex[0] = LoadGraph("./dat/img/back/texture/sakura.png");
	tex[1] = LoadGraph("./dat/img/back/texture/taiyo.png");
	tex[2] = LoadGraph("./dat/img/back/texture/kaede.png");
	tex[3] = LoadGraph("./dat/img/back/texture/yuki.png");
}

void Texture::main(int enemy) {
	num = enemy;
	update();
	if (count > 0 && num >= 0 && num < TEXNUM) draw();
}

bool Texture::update()
{
	if (num >= 0) {
		count++;
		if(num % 2 == 0) angle -= Define::PI / 300.0f;
		else angle += Define::PI / 300.0f;
	}
	else {
		count = 0;
		angle = 0.0f;
	}
	return true;
}

void Texture::draw() const
{
	DrawRotaGraphF((float)Define::CENTER_X, (float)Define::CENTER_Y, 1.0, (double)angle, tex[num], TRUE);
}
