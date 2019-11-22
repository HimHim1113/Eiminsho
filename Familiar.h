#pragma once

#include "Ball.h"


class Familiar final {

public:
	float x, y, vx, vy, ang, spd, ran;
	int fl, cnt, knd, img, sta, hp, dmg;

	void update_shiki();
	void damage_shiki(BullP *);
};