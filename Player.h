#pragma once

#include "Ball.h"


class Player final
{
public:
	Player();
	~Player() = default;

	const static int CHAR_NUM = 3;


	int main(float, float, int, int, int);
	void ini(int);

	BullP *getpbul() const { return pbul; }
	int getpower() const { return power; }
	float getx() const { return _x; }
	float gety() const { return _y; }
	int getzanki() const { return zanki; }
	int getbomb() const { return bomb; }
	int getbombflag() const { return bomb_flag; }
	
private:
	const static float MOVESPEED;
	const static int BALL_NUM = 3;
	const int BOMB_MAX;

	BullP *pbul;
	Ball ball[BALL_NUM];

	int flag;       //フラグ
	int cnt, bomb_cnt;        //カウンタ
	int shot_cnt;
	int slow_cnt;
	int human;
	int power;      //パワー
	int point;      //ポイント
	int score;      //スコア
	int mutekicnt;  //無敵状態とカウント
	int shot_mode;  //ショットモード
	int money;      //お金
	int slow;       //スローかどうか
	int zanki, bomb;      //残機数とボム数
	int bomb_flag;
	int img;        //画像
	int img_hit;
	int img_ch[2];
	int img_cshot[2];
	int img_bom;
	int img_ball;
	int sound_cshot, sound_cdeath, sound_bom;
	float _x, _y;     //座標

	void move();
	void ball_move();
	void draw() const;

	int hit_cshot(float, float, int);
	void death_move();
	int search_cshot();
	bool update_cshot();
	void ch0_shot_pattern();
	void ch1_shot_pattern();
	void ch_shot_homing(float, float, int);
	void ch_shot_forward();
	void ch_shot_spread();
};
