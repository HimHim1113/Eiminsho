#pragma once

#include "BaseMenu.h"

class Help final : public BaseMenu
{
public:
	Help() { font = CreateFontToHandle("ƒƒCƒŠƒI", 20, 2, DX_FONTTYPE_ANTIALIASING_EDGE); }
	~Help() = default;

	int draw();

private:
	int font;
};