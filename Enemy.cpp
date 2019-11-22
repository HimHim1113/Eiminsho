#include "Enemy.h"
#include <DxLib.h>
#include <cmath>
#include <cstring>
#include "Define.h"


//レーザー当たり判定デバッグ用
void myDrawSquare(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	DrawTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, GetColor(255, 0, 0), TRUE);
	DrawTriangle((int)x0, (int)y0, (int)x3, (int)y3, (int)x2, (int)y2, GetColor(255, 0, 0), TRUE);
}

Enemy::Enemy() :
	flag(0),
	count(-120),
	time(-99),
	spell_num(0),
	hitrange_bullet{ 
		 5.5f * 0.99f,//Small
		 4.0f * 0.99f,//Barrier
		 4.0f * 0.99f,//SparkSmall
		 5.0f * 0.99f,//Kome
		 4.5f * 0.99f,//Umaibo
		 9.0f * 0.99f,//SparkBig
		11.0f * 0.99f,//Kodama	//実測12.0f
		 6.5f * 0.99f,//Yosei
		 9.0f * 0.99f,//Ring
		11.0f * 0.99f,//Ame
		21.5f * 0.99f,//Tama	//実測23.0f
		32.0f * 0.99f,//Odama	//実測38.0f
		 2.8f * 0.99f,//Laser
		10.0f * 0.99f,//Ofuda
		 5.0f * 0.99f,//Star
		 6.0f * 0.99f,//Rain
		 9.0f * 0.99f,//Rainbow
		 3.0f * 0.99f,//bkumaibo
		 4.0f * 0.99f,//tubu
		 5.5f * 0.99f,//knife
},
str{
	"",
	"",
	"春眠「春眠暁を覚えず」",
	"",
	"夏眠「鷹の爪日光」",
	"",
	"秋眠「笛兎地音台風襲来」",
	"",
	"冬眠「冬将軍一凍星」",
	"「四季折々の弾幕」",
	"春夏秋冬「し☆き永眠」"
}
{
	fam = new Familiar[SHIKI_MAX];
	bul = new Bullet[BULLET_MAX];
	laz = new Lazer[LAZER_MAX];

	img_enemy[0] = LoadGraph("./dat/img/char/minmin/shunmin0.png");
	img_enemy[1] = LoadGraph("./dat/img/char/minmin/kamin0.png");
	img_enemy[2] = LoadGraph("./dat/img/char/minmin/akikaze0.png");
	img_enemy[3] = LoadGraph("./dat/img/char/minmin/toumin0.png");
	img_back[0] = LoadGraph("./dat/img/back/image0.png");
	img_back[1] = LoadGraph("./dat/img/back/image1.png");
	img_enex = LoadGraph("./dat/img/char/enex.png");

	LoadDivGraph("./dat/img/bullet/00.small.png", 8, 8, 1, 16, 16, img_bullet[0]);
	LoadDivGraph("./dat/img/bullet/01.barrier.png", 8, 8, 1, 28, 30, img_bullet[1]);
	LoadDivGraph("./dat/img/bullet/02.sparkSmall.png", 8, 8, 1, 38, 38, img_bullet[2]);
	LoadDivGraph("./dat/img/bullet/03.kome.png", 8, 8, 1, 18, 31, img_bullet[3]);
	LoadDivGraph("./dat/img/bullet/04.umaibo.png", 8, 8, 1, 64, 64, img_bullet[4]);
	LoadDivGraph("./dat/img/bullet/05.sparkBig.png", 8, 8, 1, 76, 76, img_bullet[5]);
	LoadDivGraph("./dat/img/bullet/06.kodama.png", 8, 8, 1, 32, 32, img_bullet[6]);
	LoadDivGraph("./dat/img/bullet/07.yosei.png", 8, 8, 1, 54, 54, img_bullet[7]);
	LoadDivGraph("./dat/img/bullet/08.ring.png", 8, 8, 1, 36, 36, img_bullet[8]);
	LoadDivGraph("./dat/img/bullet/09.ame.png", 8, 8, 1, 30, 57, img_bullet[9]);
	LoadDivGraph("./dat/img/bullet/10.tama.png", 8, 8, 1, 62, 62, img_bullet[10]);
	LoadDivGraph("./dat/img/bullet/11.odama.png", 8, 8, 1, 108, 108, img_bullet[11]);
	LoadDivGraph("./dat/img/bullet/12.laser.png", 8, 8, 1, 12, 240, img_bullet[12]);
	LoadDivGraph("./dat/img/bullet/13.ofuda.png", 8, 4, 2, 30, 49, img_bullet[13]);
	LoadDivGraph("./dat/img/bullet/14.star.png", 8, 8, 1, 34, 34, img_bullet[14]);
	LoadDivGraph("./dat/img/bullet/15.rain.png", 8, 8, 1, 20, 34, img_bullet[15]);
	LoadDivGraph("./dat/img/bullet/16.rainbow.png", 8, 8, 1, 20, 20, img_bullet[16]);
	LoadDivGraph("./dat/img/bullet/17.bkumaibo.png", 8, 8, 1, 28, 40, img_bullet[17]);
	LoadDivGraph("./dat/img/bullet/18.tubu.png", 9, 9, 1, 12, 18, img_bullet[18]);

	LoadDivGraph("./dat/img/bullet/laserBody0.png", 2, 2, 1, 60, 920, img_lazer[0]);
	LoadDivGraph("./dat/img/bullet/laserBody1.png", 2, 2, 1, 60, 920, img_lazer[1]);
	LoadDivGraph("./dat/img/bullet/laserBody2.png", 8, 8, 1, 12, 240, img_lazer[2]);
	LoadDivGraph("./dat/img/bullet/laserRoot0.png", 2, 2, 1, 60, 60, img_lazer_root[0]);
	LoadDivGraph("./dat/img/bullet/laserRoot1.png", 2, 2, 1, 10, 10, img_lazer_root[1]);
	LoadDivGraph("./dat/img/bullet/laserRoot2.png", 2, 2, 1, 60, 60, img_lazer_root[2]);

	image_shiki[0] = LoadGraph("./dat/img/char/shikigami/sun.png");
	image_shiki[1] = LoadGraph("./dat/img/char/minmin/shunmin0.png");
	image_shiki[2] = LoadGraph("./dat/img/char/minmin/kamin0.png");
	image_shiki[3] = LoadGraph("./dat/img/char/minmin/akikaze0.png");
	image_shiki[4] = LoadGraph("./dat/img/char/minmin/toumin0.png");

	sound_shot1 = LoadSoundMem("./dat/se/enemy_shot1.wav");
	sound_shot2 = LoadSoundMem("./dat/se/enemy_shot2.wav");
	sound_death = LoadSoundMem("./dat/se/boss_death.wav");
	sound_hit = LoadSoundMem("./dat/se/hit.wav");
	sound_fihit = LoadSoundMem("./dat/se/final_hit.wav");
	sound_time = LoadSoundMem("./dat/se/endtime.wav");
	sound_lazer = LoadSoundMem("./dat/se/lazer.wav");

	ChangeVolumeSoundMem(100, sound_shot1);
	ChangeVolumeSoundMem(100, sound_shot2);
	ChangeVolumeSoundMem(200, sound_death);
	ChangeVolumeSoundMem(50, sound_hit);
	ChangeVolumeSoundMem(100, sound_fihit);
	ChangeVolumeSoundMem(200, sound_time);
	ChangeVolumeSoundMem(100, sound_lazer);

	for (int i = 0; i < BULLET_MAX; i++) {
		bul[i].fl = 0;
	}
}

Enemy::~Enemy()
{
	delete[] fam;
	delete[] bul;
	delete[] laz;
}

int Enemy::main(int pattern, float px, float py, BullP *pbul, int damage, int bomb_flag, int talk_flag) {
	if (bomb_flag == 1) {
		for (int i = 0; i < BULLET_MAX; i++) {
			if(bul[i].fl == 1 || bul[i].fl == 2) bul[i].fl = 0;
		}
	}
	for (int i = 0; i < SHIKI_MAX; i++) fam[i].damage_shiki(pbul);
	if (flag <= 5) {
		if (count >= 0 && talk_flag == 0) (this->*enemy_pattern[spell_num])(px, py);
		update(damage, talk_flag);
		hit_flag = hit_shot(px, py);
		graze += count_graze(px, py);
	}
	else hit_flag = death();
	draw();
	return hit_flag;
}
	
void Enemy::ini(int lev) {
	flag = 0;
	count = -180;
	time = -99;
	graze = 0;
	change = 0;
	level = lev;
	person_num = 0;
	spell_num = 10;
	hp = hp_max = 0;
	move_flag = 0;
	_x = (float)Define::CENTER_X;
	_y = 150.0f;
	speed = 0.0f;
	move_count = 0;
	for (int i = 0; i < BULLET_MAX; i++) bul[i].fl = 0;
	for (int i = 0; i < BULLET_MAX; i++) bul[i].grz = 0;
	for (int i = 0; i < LAZER_MAX; i++) laz[i].fl = 0;
	for (int i = 0; i < SHIKI_MAX; i++) fam[i].fl = 0;
}

void Enemy::update(int damage, int talk_flag) {
	if (talk_flag == 0) count++;
	if (move_count > 0 && move_flag >= 1) {
		move_count--;
		_x += cosf(angle) * speed;
		_y += sinf(angle) * speed;
	}
	if (count % 60 == 59 && time > 0) {
		time--;
		if (time <= 5) PlaySoundMem(sound_time, DX_PLAYTYPE_BACK);
	}
	if (flag <= 5) {
		hp -= damage;
		if (damage > 0) {
			if (hp < hp_max / 10) PlaySoundMem(sound_fihit, DX_PLAYTYPE_BACK);
			else PlaySoundMem(sound_hit, DX_PLAYTYPE_BACK);
		}
		if (hp < 0 || time == 0) hp = 0;
		if (hp == 0 && flag != 0) {
			if (spell_num < ENEMY_PATTERN_MAX - 1) {
				flag = 0;
				move_count = 0;
				if (change % 2 == 1) {
					move(_x < Define::CENTER_X ? -100.0f : Define::OUT_W + 100.0f, -200.0f, 60);
					count = -240;
				}
				else count = -120;
				spell_num++;
				for (int i = 0; i < BULLET_MAX; i++) bul[i].fl = 0;
				for (int i = 0; i < LAZER_MAX; i++) laz[i].fl = 0;
				for (int i = 0; i < SHIKI_MAX; i++) fam[i].fl = 0;
			}
			else flag = 10;
		}
		if (hp == 0 && change == 1 && count == -120) {
			if (person_num < ENEMY_MAX - 1) person_num++;
			move((float)Define::CENTER_X, 150.0f, 60);
		}
		if (move_flag == 2 && count == -90) move((float)Define::CENTER_X, 150.0f, 60);
	}
	str_leng = strlen(str[spell_num]);
	str_x = GetDrawStringWidth(str[spell_num], str_leng);
}

int Enemy::death() {
	if (flag == 10) {
		for (int i = 0; i < BULLET_MAX; i++) bul[i].fl = 0;
		for (int i = 0; i < LAZER_MAX; i++) laz[i].fl = 0;
		for (int i = 0; i < SHIKI_MAX; i++) fam[i].fl = 0;
		flag = 20;
		count = 0;
		PlaySoundMem(sound_death, DX_PLAYTYPE_BACK);
	}
	else if (flag == 20) {
		count++;
		if (count == 180) {
			flag = 0;
			return -999;
		}
	}
	return 0;
}

void Enemy::move(int mcnt) {
	move_count = mcnt;
	float dx = _x + GetRand(2000) / 10.0f - 100.0f;
	float dy = _y + GetRand(1000) / 10.0f - 60.0f;
	if (((_x < Define::CENTER_X / 2.0f && dx < _x) || (_x > Define::CENTER_X * 3.0f / 2.0f && dx > _x)) && GetRand(2) != 0) dx = _x * 2 - dx;

	if (dx < (float)Define::IN_X) dx = (float)Define::IN_X;
	else if (dx > (float)(Define::IN_X + Define::IN_W)) dx = (float)(Define::IN_X + Define::IN_W);
	if (dy < (float)Define::IN_Y) dy = (float)Define::IN_Y;
	else if (dy > Define::IN_Y + 200.0f) dy = Define::IN_Y + 200.0f;
	angle = atan2f(dy - _y, dx - _x);
	speed = sqrtf((dx - _x) * (dx - _x) + (dy - _y) * (dy - _y)) / move_count;
}

void Enemy::move(float dx, float dy, int mcnt) {
	move_count = mcnt;
	angle = atan2f(dy - _y, dx - _x);
	speed = sqrtf((dx - _x) * (dx - _x) + (dy - _y) * (dy - _y)) / move_count;
}

void Enemy::draw() const {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	if (flag == 1 || flag == 3) DrawRotaGraphF(_x, _y, 0.3f + 0.1f * sinf(count / 100.0f), count / 90.0f, img_back[change % 2], TRUE);
	if (flag == 0 || flag == 1) DrawRotaGraphF(_x, _y, 1.0, 0.0, img_enemy[person_num], TRUE);
	else if (flag == 3) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 100);
		DrawRotaGraphF(_x, _y, 1.0, 0.0, img_enemy[person_num], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	for (int i = 0; i < SHIKI_MAX; i++) {
		if (fam[i].fl % 10 == 1) DrawRotaGraphF(fam[i].x, fam[i].y, 1.0, fam[i].ang + Define::PI / 2.0, image_shiki[fam[i].img], TRUE);
		else if (fam[i].fl % 10 == 2) {
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 100);
			DrawRotaGraphF(fam[i].x, fam[i].y, 1.0, fam[i].ang + Define::PI / 2.0, image_shiki[fam[i].img], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	for (int i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl == 1) {
			DrawRotaGraphF(laz[i].startpt.x, laz[i].startpt.y, 1.0, 0, img_lazer_root[laz[i].knd][laz[i].col], TRUE);
			DrawModiGraphF(//レーザーを描画
				laz[i].disppt[0].x, laz[i].disppt[0].y,
				laz[i].disppt[1].x, laz[i].disppt[1].y,
				laz[i].disppt[2].x, laz[i].disppt[2].y,
				laz[i].disppt[3].x, laz[i].disppt[3].y,
				img_lazer[laz[i].knd][laz[i].col], TRUE
			);
			/*
			myDrawSquare(//当たり判定範囲を表示
				laz[i].outpt[0].x, laz[i].outpt[0].y,
				laz[i].outpt[1].x, laz[i].outpt[1].y,
				laz[i].outpt[2].x, laz[i].outpt[2].y,
				laz[i].outpt[3].x, laz[i].outpt[3].y
			);
			*/
		}
	}
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl == 1 || bul[i].fl == 3) DrawRotaGraphF(bul[i].x, bul[i].y, 1.0, bul[i].ang + Define::PI / 2.0, img_bullet[bul[i].knd][bul[i].col], TRUE);
		else if (bul[i].fl == 2 || bul[i].fl == 4) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);		//ブレンドモードをα(128/255)に設定
			DrawRotaGraphF(bul[i].x, bul[i].y, 1.0, bul[i].ang + Define::PI / 2.0, img_bullet[bul[i].knd][bul[i].col], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをα(128/255)に設定
		}
	}

	if (hp_max > 0) DrawBox(Define::IN_X, 15, (int)(Define::IN_X + Define::IN_W * hp / hp_max), Define::IN_Y - 5, GetColor(255, 255, 255), TRUE);
	DrawFormatString(Define::OUT_W - 30, 10, GetColor(255, 255, 255), "%3d", time);
	if (count >= 0) DrawString(Define::IN_X + Define::IN_W - str_x, Define::IN_Y + 10, str[spell_num], GetColor(255, 255, 255));
	DrawGraph((int)_x - 10, Define::OUT_H - 20, img_enex, TRUE);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
