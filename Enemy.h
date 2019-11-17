#pragma once
#include "Bullet.h"
#include "Lazer.h"
#include "Familiar.h"
#include "Ball.h"


class Enemy final {
public:
	Enemy();
	~Enemy();

	int main(int, float, float, BullP *, int, int, int);
	void ini(int);

	int getflag() const { return flag; }
	float getx() const { return _x; }
	float gety() const { return _y; }
	int getspell() const { return spell_num; }
	int getgraze() const { return graze; }

private:
	static const int ENEMY_MAX = 4, ENEMY_PATTERN_MAX = 11, BULLET_MAX = 10000, LAZER_MAX = 100, SHIKI_MAX = 10;

	float _x, _y, vx, vy, angle, speed;
	int flag, hit_flag, count, time, hp, hp_max, img, person_num, spell_num, move_flag, move_count, level, graze, change;
	int img_enemy[ENEMY_MAX], img_back[2], img_enex, img_bullet[20][10], img_lazer[3][10], img_lazer_root[3][10], image_shiki[2]; //’e–‹—p‰æ‘œ
	const float hitrange_bullet[20];
	int sound_shot1, sound_shot2, sound_death, sound_hit, sound_fihit, sound_time, sound_lazer;
	char str[ENEMY_PATTERN_MAX][100];
	int str_x, str_leng;

	Familiar *fam;
	Bullet *bul;
	Lazer *laz;

	void update(int, int);
	void draw() const;
	void move(int);
	void move(float, float, int);
	int hit_shot(float, float);
	int death();

	int search_bull() const;
	int search_bull(int, int) const;
	int search_lazer() const;
	int search_shiki() const;

	int count_graze(float, float);

	int out_lazer(float, float);
	void input_lphy(Lazer *, int, float);
	void lazer_calc();
	void lazer_calc2();
	void conv_pos0(float*, float*, float, float, float, float, float);
	void move_bull();
	void update_shiki();

	void enemy_pattern0000(float, float);
	void enemy_pattern0001(float, float);
	void enemy_pattern0002(float, float);
	void enemy_pattern0003(float, float);
	void enemy_pattern0004(float, float);
	void enemy_pattern0005(float, float);
	void enemy_pattern0006(float, float);
	void enemy_pattern0007(float, float);
	void enemy_pattern0008(float, float);
	void enemy_pattern0009(float, float);
	void enemy_pattern0010(float, float);


	void(Enemy::*enemy_pattern[ENEMY_PATTERN_MAX])(float, float) = {
		&Enemy::enemy_pattern0000, &Enemy::enemy_pattern0001, &Enemy::enemy_pattern0002,
		&Enemy::enemy_pattern0003, &Enemy::enemy_pattern0004, &Enemy::enemy_pattern0005,
		&Enemy::enemy_pattern0006, &Enemy::enemy_pattern0007, &Enemy::enemy_pattern0008,
		&Enemy::enemy_pattern0009, &Enemy::enemy_pattern0010,
	};
};
