#pragma once

#include "BaseMenu.h"

class Help final : public BaseMenu
{
public:
	Help();
	~Help() = default;

	int draw();

private:
	int font;
};