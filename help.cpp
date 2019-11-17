#include "help.h"
#include <DxLib.h>
#include "Pad.h"


int Help::draw()
{
	DrawStringToHandle(100, 200, "Zキーで「決定」もしくは「ショット」", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 250, "Xキーで「戻る」もしくは「ボム」", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 300, "エスケープキーでプレイの「中断」", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 350, "左シフトキーで自機の「低速移動」", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 400, "一応ジョイパッドにも対応してます。", GetColor(255, 255, 255), font);

	if (Pad::getIns()->get(ePad::shot) == 1) {
		//PlaySoundMem(se_decition, DX_PLAYTYPE_BACK);
		return num;
	}
	else if (Pad::getIns()->get(ePad::bom) == 1) {
		//PlaySoundMem(se_back, DX_PLAYTYPE_BACK);
		return 100;
	}
	return 0;
}