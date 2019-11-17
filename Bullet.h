#pragma once

class Bullet final {

public:
	float x, y, vx, vy, ang, spd, base_ang[1];
	int fl, cnt, till, knd, col, img, sta, grz;

	void update_bull();
};