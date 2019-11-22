#pragma once

#include "BaseMenu.h"

class LevelMenu final : public BaseMenu
{
public:
	LevelMenu();
	~LevelMenu() = default;
	void select();

private:
	const static int NAME_MAX = 3;
	const char explain[3][WORD_MAX];
};

