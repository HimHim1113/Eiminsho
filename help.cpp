#include "help.h"
#include <DxLib.h>
#include "Pad.h"


Help::Help()
{
	font = CreateFontToHandle("���C���I", 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	img = LoadGraph("./dat/img/back/menu/katakana.png");
}

int Help::draw()
{
	DrawGraph(0, 0, img, FALSE);

	DrawStringToHandle(100, 200, "Z�L�[�Łu����v�������́u�V���b�g�v", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 250, "X�L�[�Łu�߂�v�������́u�{���v", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 300, "�G�X�P�[�v�L�[�Ńv���C�́u���f�v", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 350, "���V�t�g�L�[�Ŏ��@�́u�ᑬ�ړ��v", GetColor(255, 255, 255), font);
	DrawStringToHandle(100, 400, "�W���C�p�b�h�ɂ��Ή����Ă܂��B", GetColor(255, 255, 255), font);

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