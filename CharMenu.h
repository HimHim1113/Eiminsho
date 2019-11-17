#pragma once

#include "BaseMenu.h"
#include "Player.h"

class CharMenu final : public BaseMenu
{
public:
	CharMenu();
	~CharMenu() = default;
	void select();

private:
	int char_img[Player::CHAR_NUM];
};