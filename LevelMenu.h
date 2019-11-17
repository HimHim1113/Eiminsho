#pragma once

#include "BaseMenu.h"

class LevelMenu final : public BaseMenu
{
public:
	void select();

private:
	const static int NAME_MAX = 3;
};

