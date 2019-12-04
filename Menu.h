#pragma once

#include "BaseMenu.h"

class Menu final : public BaseMenu
{
public:
	Menu() : dice(0) { img = LoadGraph("./dat/img/back/menu/katakana.png"); }
	void select();
	void setDice(int xi) { dice = xi; }
	const static int NAME_MAX = 4;

private:
	int dice;
};

