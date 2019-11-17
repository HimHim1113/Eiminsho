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
	int fl, cnt, knd, col, sta;//�t���O�A�J�E���^�A��ށA�F
	float haba, ang, length, hantei;//���A�p�x�A�����A����͈�(�\�����ɑ΂���0~1�Ŏw��)
	pt_t startpt, disppt[4], outpt[4];//���[�U�[�𔭎˂���n�_�A�\�����W�A�����蔻��͈�
	lphy_t lphy;
};