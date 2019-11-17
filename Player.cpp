#include "Player.h"
#include <DxLib.h>
#include <cmath>
#include "Define.h"
#include "Pad.h"


const float Player::MOVESPEED = 6.0;

Player::Player() :
	BOMB_MAX(3),
	slow_cnt(0),
	power(200),
	shot_mode(0),
	money(0),
	img(0),
	slow(0),
	_x((float)Define::CENTER_X), 
	_y((float)Define::CENTER_Y * 3.0f / 2.0f)
{
	pbul = new BullP[BullP::CSHOT_MAX];

	for (int i = 0; i < BullP::CSHOT_MAX; i++) {
		pbul[i].fl = 0;
	}

	ball[0].angle = -Define::PI * 2.0f / 3.0f;
	ball[1].angle = 0.0f;
	ball[2].angle = Define::PI * 2.0f / 3.0f;
	ball[0].range = ball[1].range = ball[2].range = 50.0f;

	img_hit = LoadGraph("./dat/img/char/atari.png");
	img_ch[0] = LoadGraph("./dat/img/char/shibuki/think.png");
	img_ch[1] = LoadGraph("./dat/img/char/shibuki/think.png");

	img_cshot[0] = LoadGraph("./dat/img/char/bl_00.png");
	img_cshot[1] = LoadGraph("./dat/img/char/bl_01.png");
	img_bom = LoadGraph("./dat/img/char/bom.png");
	img_ball = LoadGraph("./dat/img/char/tanipan.png");

	sound_cshot = LoadSoundMem("./dat/se/cshot.wav");
	sound_cdeath = LoadSoundMem("./dat/se/char_death.wav");
	sound_bom = LoadSoundMem("./dat/se/maspa.mp3");

	ChangeVolumeSoundMem(100, sound_cshot);
	ChangeVolumeSoundMem(200, sound_cdeath);
	ChangeVolumeSoundMem(200, sound_bom);
}

int Player::main(float ex, float ey, int hit_flag, int enemy_flag, int talk_flag)
{
	if (cnt == 0) flag = 1;
	cnt++; bomb_cnt++; mutekicnt--;
	if (bomb_cnt == -60) bomb_flag = 0;
	if (flag >= 0) {
		//img = (cnt % 24) / 6;
		if (((hit_flag == 1 && flag == 1) || (flag == 2 && cnt < -150)) && mutekicnt < 0) death_move();
		else move();
		ball_move();
		update_cshot();
		
		if (bomb_cnt >= 0) {
			if (Pad::getIns()->get(ePad::bom) == 1 && bomb > 0 && talk_flag == 0) {
				bomb--;
				bomb_cnt = -240;
				bomb_flag = 1;
				mutekicnt = 300;
				PlaySoundMem(sound_bom, DX_PLAYTYPE_BACK);
			}
			else if (!((hit_flag == 1 && flag == 1) || (flag == 2 && cnt < -150)) && talk_flag == 0) {
				//ÉVÉáÉbÉgÉ{É^ÉìÇ™âüÇ≥ÇÍÇƒÇ¢ÇΩÇÁ
				if (Pad::getIns()->get(ePad::shot) > 0) {
					shot_cnt++;
					if (shot_cnt % 3 == 0) {//3ÉJÉEÉìÉgÇ…1âÒ
						if (Pad::getIns()->get(ePad::slow) > 0) {//í·ë¨à⁄ìÆíÜÇ»ÇÁ
							ch1_shot_pattern();
						}
						else {
							ch0_shot_pattern();
						}
						switch (human) {
						case 0:
							ch_shot_homing(ex, ey, enemy_flag);
							break;
						case 1:
							ch_shot_forward();
							break;
						case 2:
							ch_shot_spread();
							break;
						default:
							break;
						}
						DxLib::PlaySoundMem(sound_cshot, DX_PLAYTYPE_BACK);
					}
				}
				else
					shot_cnt = 0;
			}
		}
	}
	int damage = hit_cshot(ex, ey, enemy_flag);
	if (bomb_flag == 1 && enemy_flag == 1) damage += 100;
	draw();
	if (flag == -1 && cnt == 0) return -999;
	else return damage * 4;
}

void Player::ini(int man) {
	flag = 1;
	cnt = 0;
	human = man;
	//human = 0;
	bomb_cnt = 0;
	bomb_flag = 0;
	zanki = 5;
	bomb = BOMB_MAX;
	mutekicnt = 180;
	score = 0;
	point = 0;
	_x = (float)Define::CENTER_X;
	_y = (float)Define::CENTER_Y * 3.0f / 2.0f;
	for (int i = 0; i < BullP::CSHOT_MAX; i++) pbul[i].fl = 0;
}

void Player::draw() const
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	if (mutekicnt >= 0 && mutekicnt % 30 < 10) SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 100);
	if (Pad::getIns()->get(ePad::slow) > 0) DrawRotaGraphF(_x, _y, 1.0f, 0.0f, img_ch[1], TRUE);
	else DrawRotaGraphF(_x, _y, 1.0f, 0.0f, img_ch[0], TRUE);
	if (mutekicnt >= 0 && mutekicnt % 30 < 15) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < BALL_NUM; i++) {
		DrawRotaGraphF(ball[i].rx, ball[i].ry, 1.0, 0.0, img_ball, TRUE);
	}
	for (int i = 0; i < BullP::CSHOT_MAX; i++) {
		if(pbul[i].fl > 0) DrawRotaGraphF(pbul[i].bx, pbul[i].by, 1.0, pbul[i].angle + Define::PI / 2.0f, img_cshot[pbul[i].knd], TRUE);
	}
	if (bomb_flag == 1) DrawModiGraphF(_x - 300, _y, _x + 300, _y, _x + 500, _y - 1000, _x - 500, _y - 1000, img_bom, TRUE);
	if (Pad::getIns()->get(ePad::slow) > 0) DrawRotaGraphF(_x, _y, 1.5f, slow_cnt / 40.0f, img_hit, TRUE);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void Player::move()
{
	float moveX = 0, moveY = 0;
	if (Pad::getIns()->get(ePad::left) > 0) {
		moveX -= MOVESPEED;
	}
	if (Pad::getIns()->get(ePad::right) > 0) {
		moveX += MOVESPEED;
	}
	if (Pad::getIns()->get(ePad::down) > 0) {
		moveY += MOVESPEED;
	}
	if (Pad::getIns()->get(ePad::up) > 0) {
		moveY -= MOVESPEED;
	}
	if (moveX && moveY) { //éŒÇﬂà⁄ìÆ
		moveX /= (float)sqrt(2.0);
		moveY /= (float)sqrt(2.0);
	}
	if (Pad::getIns()->get(ePad::slow) > 0) {//í·ë¨à⁄ìÆ
		moveX /= 3;
		moveY /= 3;
		slow_cnt++;
	}
	else slow_cnt = 0;
	
	if (moveX + _x < Define::IN_X) {//ç∂ògÇÊÇËç∂Ç»ÇÁ
		_x = (float)Define::IN_X;   //ç∂ògÇ≈é~ÇﬂÇÈ
	}
	else if (moveX + _x > Define::IN_X + Define::IN_W) {//âEògÇÊÇËâEÇ»ÇÁ
		_x = (float)(Define::IN_X + Define::IN_W);      //âEògÇ≈é~ÇﬂÇÈ
	}
	else {//ògì‡Ç»ÇÁ
		_x += moveX;//ïÅí Ç…à⁄ìÆ
	}
	if (moveY + _y < Define::IN_Y) {   //è„ògÇÊÇËè„Ç»ÇÁ
		_y = (float)Define::IN_Y;      //è„ògÇ≈é~ÇﬂÇÈ
	}
	else if (moveY + _y > Define::IN_Y + Define::IN_H) {    //â∫ògÇÊÇËâ∫Ç»ÇÁ
		_y = (float)(Define::IN_Y + Define::IN_H);          //â∫ògÇ≈é~ÇﬂÇÈ
	}
	else {//ògì‡Ç»ÇÁ
		_y += moveY;//ïÅí Ç…à⁄ìÆ
	}
}

void Player::death_move() {
	if (flag == 1) {
		flag = 2;
		_x = (float)Define::CENTER_X;
		_y = Define::OUT_H - 50.0f;
		cnt = -300;
		bomb_cnt = -150;
		bomb_flag = -1;
		zanki--;
		bomb = BOMB_MAX;
		mutekicnt = 420;
		PlaySoundMem(sound_cdeath, DX_PLAYTYPE_BACK);
	}
	if (zanki < 0) {
		flag = -1;
		for (int i = 0; i < BullP::CSHOT_MAX; i++) pbul[i].fl = 0;
		cnt = -60;
		_y = Define::OUT_H + 100.0f;
	}
}

int Player::hit_cshot(float ex, float ey, int enemy_flag) {
	int power_total = 0;
	if (enemy_flag == 1) {
		for (int i = 0; i < BullP::CSHOT_MAX; i++) {
			if (pbul[i].fl > 0) {
				float dx = ex - pbul[i].bx;
				float dy = ey - pbul[i].by;
				//íÜä‘ÇåvéZÇ∑ÇÈïKóvÇ™Ç†ÇÍÇŒ
				if (pbul[i].speed > 50.0f) {
					//ÇPÉtÉåÅ[ÉÄëOÇ…Ç¢ÇΩà íuÇäiî[Ç∑ÇÈ
					float pre_x = pbul[i].bx + cosf(pbul[i].angle + Define::PI) * pbul[i].speed;
					float pre_y = pbul[i].by + sinf(pbul[i].angle + Define::PI) * pbul[i].speed;
					float px, py;
					for (int j = 0; j < (int)(pbul[i].speed / 50.0f); j++) {//êiÇÒÇæï™ÅÄìñÇΩÇËîªíËï™ÉãÅ[Év
						px = pre_x - ex;
						py = pre_y - ey;
						if (px * px + py * py < 2500.0f) {
							pbul[i].fl = 0;
							power_total += pbul[i].power;
						}
						pre_x += cosf(pbul[i].angle) * 50.0f;
						pre_y += sinf(pbul[i].angle) * 50.0f;
					}
				}
				else if (dx * dx + dy * dy < 2500.0f) {
					pbul[i].fl = 0;
					power_total += pbul[i].power;
				}
			}
		}
	}
	return power_total;
}

void Player::ball_move() {
	for (int i = 0; i < BALL_NUM; i++) {
		if (Pad::getIns()->get(ePad::slow) > 0) {
			ball[i].range -= 1.0f;
			if (ball[i].range < 30.0f) ball[i].range = 30.0f;
		}
		else {
			ball[i].range += 1.0f;
			if (ball[i].range > 50.0f) ball[i].range = 50.0f;
		}
		ball[i].rx = _x + ball[i].range * cosf(Define::PI * (i + 1) / 4.0f);
		ball[i].ry = _y + ball[i].range * sinf(Define::PI * (i + 1) / 4.0f) + 10.0f;
	}
}


//ãÛÇ¢ÇƒÇ¢ÇÈíeî‘çÜÇï‘Ç∑
int Player::search_cshot() {
	for (int i = 0; i < BullP::CSHOT_MAX; i++) {
		if (pbul[i].fl == 0) return i;
	}
	return -1;
}

bool Player::update_cshot(){
	for (int i = 0; i < BullP::CSHOT_MAX; i++) {
		if (pbul[i].fl > 0) {
			const float dranx = pbul[i].speed + 55.0f / 2.0f, drany = pbul[i].speed + 110.0f / 2.0f;
			pbul[i].bx += cos(pbul[i].angle) * pbul[i].speed;
			pbul[i].by += sin(pbul[i].angle) * pbul[i].speed;
			pbul[i].cnt++;
			if (pbul[i].bx < -dranx || pbul[i].bx > Define::OUT_W + dranx ||
				pbul[i].by < -drany || pbul[i].by > Define::OUT_W + drany)//âÊñ Ç©ÇÁäOÇÍÇΩÇÁ
				pbul[i].fl = 0;
		}
	}
	return true;
}

//í èÌÉVÉáÉbÉgìoò^
void Player::ch0_shot_pattern() {
	const float cshot0pos_x[4] = { -10.0f, 10.0f, -30.0f, 30.0f };
	const float cshot0pos_y[4] = { -30.0f, -30.0f, -10.0f, -10.0f };
	int i;
	for (int n = 0; n < (power < 200 ? 2 : 4); n++) {
		if ((i = search_cshot()) != -1) {
			pbul[i].fl = 1;
			pbul[i].cnt = 0;
			pbul[i].angle = -Define::PI / 2;
			pbul[i].speed = 20.0f;
			pbul[i].bx = _x + cshot0pos_x[n];
			pbul[i].by = _y + cshot0pos_y[n];
			pbul[i].power = 14;
			pbul[i].knd = 0;
		}
	}
	//se_flag[2] = 1;//î≠éÀâπÉIÉì
}

//í·ë¨í èÌÉVÉáÉbÉgìoò^
void Player::ch1_shot_pattern() {
	const float cshot0pos_x[4] = { -10.0f, 10.0f, -30.0f, 30.0f };
	const float cshot0pos_y[4] = { -30.0f, -30.0f, -10.0f, -10.0f };
	int i;
	for (int n = 0; n < (power < 200 ? 2 : 4); n++) {
		if ((i = search_cshot()) != -1) {
			pbul[i].fl = 1;
			pbul[i].cnt = 0;
			pbul[i].angle = -Define::PI / 2;
			pbul[i].speed = 20.0f;
			pbul[i].bx = _x + cshot0pos_x[n] / 3.0f;//í·ë¨íÜÇ»ÇÁà íuÇíÜêSë§Ç÷
			pbul[i].by = _y + cshot0pos_y[n] / 2.0f;
			pbul[i].power = 14;
			pbul[i].knd = 0;
		}
	}
	//se_flag[2] = 1;
}

//ÉzÅ[É~ÉìÉOÉVÉáÉbÉgìoò^
void Player::ch_shot_homing(float ex, float ey, int enemy_flag) {
	int i;
	for (int n = 0; n < BALL_NUM; n++) {
		if ((i = search_cshot()) != -1) {
			pbul[i].fl = 1;
			pbul[i].cnt = 0;
			if (enemy_flag == 1) pbul[i].angle = atan2f(ey - ball[n].ry, ex - ball[n].rx);
			else pbul[i].angle = -Define::PI / 2.0f;
			pbul[i].speed = 20.0f;
			pbul[i].bx = ball[n].rx;
			pbul[i].by = ball[n].ry;
			pbul[i].power = 24;
			pbul[i].knd = 1;
		}
	}
}

//ëOï˚èWíÜÉVÉáÉbÉgìoò^
void Player::ch_shot_forward() {
	int i;
	for (int n = 0; n < BALL_NUM; n++) {
		if ((i = search_cshot()) != -1) {
			pbul[i].fl = 1;
			pbul[i].cnt = 0;
			pbul[i].angle = -Define::PI / 2.0f;
			pbul[i].speed = 20.0f;
			pbul[i].bx = ball[n].rx;
			pbul[i].by = ball[n].ry;
			pbul[i].power = 48;
			pbul[i].knd = 1;
		}
	}
}

//ägéUÉVÉáÉbÉgìoò^
void Player::ch_shot_spread() {
	int i;
	for (int n = 0; n < BALL_NUM * 5; n++) {
		if ((i = search_cshot()) != -1) {
			pbul[i].fl = 1;
			pbul[i].cnt = 0;
			if (n < BALL_NUM) pbul[i].angle = -Define::PI / 2.0f;
			else if (n < BALL_NUM * 2) pbul[i].angle = -Define::PI / 2.0f - Define::PI / 12.0f;
			else if (n < BALL_NUM * 3) pbul[i].angle = -Define::PI / 2.0f + Define::PI / 12.0f;
			else if (n < BALL_NUM * 4) pbul[i].angle = -Define::PI / 2.0f - Define::PI / 8.0f;
			else pbul[i].angle = -Define::PI / 2.0f + Define::PI / 8.0f;
			pbul[i].speed = 20.0f;
			pbul[i].bx = ball[n % BALL_NUM].rx;
			pbul[i].by = ball[n % BALL_NUM].ry;
			pbul[i].power = 16;
			pbul[i].knd = 1;
		}
	}
}