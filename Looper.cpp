#include "Looper.h"
#include <DxLib.h>
#include "Keyboard.h"
#include "Pad.h"

Looper::Looper() :
	screen(0),
	end_cnt(-1),
	bgm_flag(-1)
{
	_title = new Title();
	bgm[0] = LoadSoundMem("./dat/music/0_0.mp3");
	bgm[1] = LoadSoundMem("./dat/music/1_0.mp3");

	ChangeVolumeSoundMem(90, bgm[0]);
	ChangeVolumeSoundMem(90, bgm[1]);

	se_decition = LoadSoundMem("./dat/se/decition.wav");
	se_back = LoadSoundMem("./dat/se/cancel.wav");

	ChangeVolumeSoundMem(100, se_decition);
	ChangeVolumeSoundMem(100, se_back);
}

bool Looper::loop()
{
	Keyboard::getIns()->update(); //キーボードの更新
	Pad::getIns()->update(); //ジョイパッドの更新

	if (end_cnt < 0) {
		switch (screen)
		{
		case 0:
			screen = 1;
			break;

		case 1:
			_title->main();
			if (Pad::getIns()->get(ePad::shot) == 1) {
				delete _title;
				screen = 10;
			}
			if (bgm_flag == -1) {
				bgm_flag = 0;
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
			}
			break;

		case 10:
			_menu.select();
			if (Pad::getIns()->get(ePad::shot) == 1) {
				switch (_menu.return_select()) {
				case 0:
					_menu.setDice(0);
					screen = 20;
					break;
				case 1:
					_menu.setDice(GetRand(5999) % 6 + 1);
					break;
				case 2:
					_menu.setDice(0);
					screen = 50;
					break;
				case Menu::NAME_MAX - 1:
					end_cnt = 30;
					break;
				default:
					printfDx("menuの値%dが異常です。", _menu.return_select());
					break;
				}
			}
			break;

		case 20:
			_cmenu.select();
			if (Pad::getIns()->get(ePad::shot) == 1) screen = 30; 
			else if (Pad::getIns()->get(ePad::bom) == 1) screen = 10;
			break;

		case 30:
			_lmenu.select();
			if (Pad::getIns()->get(ePad::shot) == 1) screen = 99;
			else if (Pad::getIns()->get(ePad::bom) == 1) screen = 20;
			break;

		case 50:
			if (_help.draw() == 100) screen = 10;
			break;

		case 99:
			_player.ini(_cmenu.return_select());
			_enemy.ini(_lmenu.return_select());
			_talk.ini(_enemy.getspell());
			screen = 100;
			break;

		case 100:
			_back1.update();
			_back1.draw();

			if (bgm_flag == 0) {
				bgm_flag = 1;
				StopSoundMem(bgm[0]);
				PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
			}
			damage = _player.main(_enemy.getx(), _enemy.gety(), hit_flag, _enemy.getflag(), _talk.getflag());
			if (damage < 0) {
				screen = 10;
				bgm_flag = 0;
				StopSoundMem(bgm[1]);
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
			}
			hit_flag = _enemy.main(pattern, _player.getx(), _player.gety(), _player.getpbul(), damage, _player.getbombflag(), _talk.getflag());
			if (hit_flag < 0) {
				screen = 10;
				bgm_flag = 0;
				StopSoundMem(bgm[1]);
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
			}
			_talk.main();
			_board.main(_player.getzanki(), _player.getbomb(), _enemy.getgraze());
			if (Pad::getIns()->get(ePad::start) == 1) {
				bgm_flag = 0;
				_talk.fin();
				StopSoundMem(bgm[1]);
				PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
				screen = 10;
			}
			break;

		default:
			printfDx("screenの値%dが異常です。", screen);
			break;
		}

		if (screen < 100) {
			if (Pad::getIns()->get(ePad::shot) == 1) PlaySoundMem(se_decition, DX_PLAYTYPE_BACK);
			else if (Pad::getIns()->get(ePad::bom) == 1) PlaySoundMem(se_back, DX_PLAYTYPE_BACK);
		}
	}

	_fps.draw();
	_fps.wait();
	
	if (--end_cnt == 0) return false;
	else return true;
}
