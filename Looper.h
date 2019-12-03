#pragma once

#include "Fps.h"
#include "Title.h"
#include "Menu.h"
#include "CharMenu.h"
#include "LevelMenu.h"
#include "help.h"
#include "Talk.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "Back01.h"
#include "BackSpell.h"
#include "Texture.h"


class Looper final
{
public:
	Looper();
	~Looper() = default;
	bool loop();

private:
	int screen, end_cnt, pattern, level, damage, hit_flag;
	int bgm[2], bgm_flag;
	int se_decition, se_back;

	Fps _fps;
	Title *_title;
	Menu _menu;
	CharMenu _cmenu;
	LevelMenu _lmenu;
	Help _help;
	Talk _talk;
	
	Player _player;
	Enemy _enemy;
	Board _board;

	Back01 _back1;
	BackSpell _backs;
	Texture _tex;
};
