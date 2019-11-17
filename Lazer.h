#pragma once


struct pt_t final {
	float x, y;
};

struct lphy_t final {
	int conv_flag;
	float time, base_ang, ang;
	float conv_x, conv_y, conv_base_x, conv_base_y;
};

struct Lazer final {
	int fl, cnt, knd, col, sta;//フラグ、カウンタ、種類、色
	float haba, ang, length, hantei;//幅、角度、長さ、判定範囲(表示幅に対して0~1で指定)
	pt_t startpt, disppt[4], outpt[4];//レーザーを発射する始点、表示座標、当たり判定範囲
	lphy_t lphy;
};