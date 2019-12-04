#pragma once

#include <DxLib.h>

class BaseMenu
{
public:
	BaseMenu() :
		num(0)
	{ font = CreateFontToHandle("ƒƒCƒŠƒI", 50, 2, DX_FONTTYPE_ANTIALIASING_EDGE); }
	~BaseMenu() = default;

	int return_select() { return num; }

protected:
	const static int WORD_MAX = 100;
	int num, font, img;
};