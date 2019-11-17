#include "Title.h"
#include <DxLib.h>


Title::Title()
{
	font = CreateFontToHandle("ƒƒCƒŠƒI", 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void Title::main() {
	DrawStringToHandle(300, 200, "‚ê–‚Ü˜^", GetColor(255, 255, 255), font);
	DrawStringToHandle(300, 400, "Press Z", GetColor(255, 255, 255), font);
}
