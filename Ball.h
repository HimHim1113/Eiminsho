#pragma once


struct BullP {
	int fl, power, cnt, knd;
	float bx, by, angle, speed;
	const static int CSHOT_MAX = 500;
};

struct Ball {
	float rx, ry, range, angle;
};