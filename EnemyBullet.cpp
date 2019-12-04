#include "Enemy.h"
#include <DxLib.h>
#include <cmath>
#include "Define.h"


//OK
void Enemy::enemy_pattern0000(float px, float py) {
	if (count == 0) {
		time = 35;
		hp_max = 35000;
		hp = hp_max;
		flag = 1;
		change = 2;
		move_flag = 2;
	}

	int shot_count, shot_num1, shot_num2;
	switch (level) {
	case 0:
		shot_count = 10;
		shot_num1 = 6;
		shot_num2 = 1;
		break;
	case 1:
		shot_count = 10;
		shot_num1 = 4;
		shot_num2 = 2;
		break;
	case 2:
		shot_count = 10;
		shot_num1 = 4;
		shot_num2 = 3;
		break;
	default:
		shot_count = 60;
		shot_num1 = 1;
		shot_num2 = 1;
		break;
	}
	int a;

	if (count == 0) move(_x, _y, 1);
	if (count % 120 == 0 && count >= 120) move(115);
	static float rang[3] = { GetRand(62831) / 10000.0f, GetRand(62831) / 10000.0f, GetRand(62831) / 10000.0f };

	if (count % shot_count == 0) {
		for (int i = 0; i < shot_num1; i++) {
			for (int j = 0; j < shot_num2; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = _x;
					bul[a].y = _y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 3.0f + level * 0.5f - j;
					bul[a].ang = Define::PI * 2.0f * i / shot_num1 + count / (77.7f + j * 10.0f) + rang[j];
					bul[a].knd = 3;
					bul[a].col = (i % 2 == 0 ? 2 : 3);
					bul[a].till = 300;
					bul[a].grz = 1;
					bul[a].cnt = 0;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = _x;
					bul[a].y = _y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 3.0f + level * 0.5f - j;
					bul[a].ang = Define::PI * 2.0f * i / shot_num1 - count / (77.7f + j * 10.0f) + rang[j];
					bul[a].knd = 3;
					bul[a].col = (i % 2 == 0 ? 5 : 7);
					bul[a].till = 300;
					bul[a].grz = 1;
					bul[a].cnt = 0;
				}
			}
		}
		DxLib::PlaySoundMem(sound_shot2, DX_PLAYTYPE_BACK);
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0001(float px, float py) {
	if (count == 0) {
		time = 30;
		hp_max = 25000;
		hp = hp_max;
		flag = 1;
		change = 0;
		move_flag = 1;
	}
	int a;

	int shot_count;
	switch (level) {
	case 0:
		shot_count = 16;
		break;
	case 1:
		shot_count = 10;
		break;
	case 2:
		shot_count = 5;
		break;
	default:
		shot_count = 30;
		break;
	}

	move(300.0f * sinf(Define::PI * count / 300.0f) + (float)Define::CENTER_X, _y, 1);

	if (count % shot_count == 0) {
		for (int i = 0; i < 3; i++) {
			if ((a = search_bull()) >= 0) {
				bul[a].fl = 1;
				bul[a].x = _x;
				bul[a].y = _y;
				bul[a].vx = GetRand(400) / 100.0f - 2.0f;
				bul[a].vy = -GetRand(300) / 100.0f - 3.0f;
				bul[a].spd = 0.0f;
				//bul[a].ang = 0.0f;
				bul[a].knd = 1;
				bul[a].col = 2;
				bul[a].till = 300;
				bul[a].grz = 1;
				bul[a].cnt = 0;
				bul[a].sta = GetRand(2000) - 1000;
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}
	
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].cnt <= 240) bul[i].vy += 0.04f;
			else if (bul[i].cnt < 360) bul[i].vx += bul[i].sta / 30000.0f;
			bul[i].ang = atan2f(bul[i].vy, bul[i].vx);
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0002(float px, float py) {
	if (count == 0) {
		time = 45;
		hp_max = 50000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}
	back_tex = 0;
	int shot_count;
	switch (level) {
	case 0:
		shot_count = 20;
		break;
	case 1:
		shot_count = 10;
		break;
	case 2:
		shot_count = 6;
		break;
	default:
		shot_count = 60;
		break;
	}
	int a, b;

	if (count % 120 == 0) move(90);

	if (count % shot_count == 0) {
		if ((a = search_bull()) >= 0) {
			bul[a].fl = 1;
			bul[a].x = GetRand((Define::OUT_W + 50) * 100) / 100.0f - 25.0f;
			bul[a].y = -50.0f;
			bul[a].vx = 0.0f;
			bul[a].vy = 0.0f;
			bul[a].spd = 2.0f;
			bul[a].ang = Define::PI / 2.0f + GetRand(1000) / 1000.0f - 0.5f;
			bul[a].knd = 6;
			bul[a].col = 2;
			bul[a].till = 100;
			bul[a].grz = 1;
			bul[a].cnt = 0;
			bul[a].sta = -1;
			bul[a].base_ang[0] = GetRand(62832) / 10000.0f;
		}
		for (int i = 0; i < 5; i++) {
			if ((b = search_bull()) >= 0) {
				bul[b].fl = 1;
				bul[b].ang = bul[a].base_ang[0] + Define::PI * 2.0f * i / 5.0f;
				bul[b].x = bul[a].x + cosf(bul[b].ang) * 15.0f;
				bul[b].y = bul[a].y + sinf(bul[b].ang) * 15.0f;
				bul[b].vx = cosf(bul[a].ang) * bul[a].spd;
				bul[b].vy = sinf(bul[a].ang) * bul[a].spd;
				bul[b].spd = 0.0f;
				bul[b].knd = 15;
				bul[b].col = 2;
				bul[b].till = 100;
				bul[b].grz = 1;
				bul[b].cnt = 0;
				bul[b].sta = 0;
			}
		}
		bul[a].fl = 0;
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].sta >= 0 && (bul[i].cnt >= 150 && bul[i].cnt < 210)) {
				bul[i].spd += 0.06f + level * 0.015f;
				bul[i].vx /= 1.1f;
				bul[i].vy /= 1.1f;
			}
			if (bul[i].sta >= 0 && bul[i].cnt == 210) bul[i].vx = bul[i].vy = 0.0f;
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0003(float px, float py) {
	if (count == 0) {
		time = 30;
		hp_max = 30000;
		hp = hp_max;
		flag = 1;
		change = 0;
		move_flag = 2;
	}

	int shot_count, shot_num1, shot_num2;
	switch (level) {
	case 0:
		shot_count = 90;
		shot_num1 = 16;
		shot_num2 = 1;
		break;
	case 1:
		shot_count = 60;
		shot_num1 = 16;
		shot_num2 = 2;
		break;
	case 2:
		shot_count = 50;
		shot_num1 = 24;
		shot_num2 = 3;
		break;
	default:
		shot_count = 300;
		shot_num1 = 4;
		shot_num2 = 1;
		break;
	}
	int a;
	static int shiki_num = 0;

	if (count % 90 == 0 && count >= 270) move(60);

	if (count == 0) {
		if ((a = search_shiki()) >= 0) {
			fam[a].fl = 1;
			fam[a].x = _x;
			fam[a].y = _y;
			fam[a].vx = 0.0f;
			fam[a].vy = 0.0f;
			fam[a].ang = 0.0f;
			fam[a].spd = 0.0f;
			fam[a].cnt = 0;
			fam[a].knd = 0;
			fam[a].img = 0;
			fam[a].sta = 0;
		}
		shiki_num = a;
	}

	if (count % shot_count == 0 && count >= 180) {
		float rang1 = GetRand(62831) / 10000.0f, rang2 = GetRand(62831) / 10000.0f;
		for (int i = 0; i < shot_num1; i++) {
			for (int j = 0; j < shot_num2; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = fam[shiki_num].x;
					bul[a].y = fam[shiki_num].y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 4.0f - j * 1.0f;
					bul[a].ang = Define::PI * 2.0f * i / shot_num1 + rang1;
					bul[a].knd = 9;
					bul[a].col = 3;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 0;
				}
			}
			if ((a = search_bull()) >= 0) {
				bul[a].fl = 1;
				bul[a].x = fam[shiki_num].x;
				bul[a].y = fam[shiki_num].y;
				bul[a].vx = 0.0f;
				bul[a].vy = 0.0f;
				bul[a].spd = 6.0f;
				bul[a].ang = Define::PI * 2.0f * i / shot_num1 + rang2;
				bul[a].knd = 2;
				bul[a].col = 5;
				bul[a].till = 300;
				bul[a].grz = 1;
				bul[a].cnt = 0;
				bul[a].sta = 1;
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].sta == 1) {
				if (bul[i].cnt == 30) bul[i].spd = 0.0f;
				if (bul[i].cnt == 120) bul[i].ang = atan2f(py - bul[i].y, px - bul[i].x);
				if (bul[i].cnt >= 120 && bul[i].cnt <= 160) bul[i].spd  += 0.1f;
			}
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0004(float px, float py) {
	if (count == 0) {
		time = 45;
		hp_max = 50000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}
	back_tex = 1;
	int shot_num;
	switch (level) {
	case 0:
		shot_num = 16;
		break;
	case 1:
		shot_num = 28;
		break;
	case 2:
		shot_num = 48;
		break;
	default:
		shot_num = 2;
		break;
	}
	int a;
	static int shiki_num = 0;

	if (count % 90 == 0 && count >= 270) move(60);

	if (count == 0) {
		if ((a = search_shiki()) >= 0) {
			fam[a].fl = 1;
			fam[a].x = _x;
			fam[a].y = _y;
			fam[a].vx = 0.0f;
			fam[a].vy = 0.0f;
			fam[a].ang = 0.0f;
			fam[a].spd = 0.0f;
			fam[a].cnt = 0;
			fam[a].knd = 0;
			fam[a].img = 0;
			fam[a].sta = 0;
		}
		shiki_num = a;
	}

	if (count >= 180) {
		float rang1 = GetRand(62831) / 10000.0f, rang2 = GetRand(62831) / 10000.0f;
		for (int i = 0; i < shot_num; i++) {
			if ((a = search_bull()) >= 0) {
				bul[a].fl = 1;
				bul[a].x = fam[shiki_num].x;
				bul[a].y = fam[shiki_num].y;
				bul[a].vx = 0.0f;
				bul[a].vy = 0.0f;
				bul[a].spd = 10.0f;
				bul[a].ang = Define::PI * 2.0f * i / shot_num + count / 120.0f;
				bul[a].knd = 16;
				bul[a].col = 2;
				bul[a].till = 0;
				bul[a].grz = 1;
				bul[a].cnt = 0;
				bul[a].sta = count % 10 == 0 ? 1 : 0;
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].sta >= 0) {
				if ((px - bul[i].x) * (px - bul[i].x) + (py - bul[i].y) * (py - bul[i].y) < 10000.0f) {
					if (bul[i].sta == 1) {
						bul[i].spd = 0.0f;
						bul[i].ang += GetRand(300) / 1000.0f - 0.2f;
						bul[i].knd = 18;
						bul[i].col = 5;
						bul[i].grz = 1;
						bul[i].cnt = 0;
						bul[i].sta = -1;
					}
					else bul[i].fl = 0;
				}
			}
			else if (bul[i].sta == -1) {
				if (bul[i].cnt <= 40) {
					bul[i].spd += 0.05f;
				}
			}
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0005(float px, float py) {
	if (count == 0) {
		time = 30;
		hp_max = 30000;
		hp = hp_max;
		flag = 1;
		change = 0;
		move_flag = 1;
	}

	int shot_num1, shot_num2;
	switch (level) {
	case 0:
		shot_num1 = 3;
		shot_num2 = 2;
		break;
	case 1:
		shot_num1 = 4;
		shot_num2 = 3;
		break;
	case 2:
		shot_num1 = 6;
		shot_num2 = 4;
		break;
	default:
		shot_num1 = 2;
		shot_num2 = 1;
		break;
	}
	int a;
	static float rang;

	if (count % 90 == 0 && count >= 90) move(60);
	if (count % 300 == 0) rang = GetRand(62831) / 10000.0f;

	if (count % 6 == 0 && count % 600 < 240) {
		for (int i = 0; i < shot_num1; i++) {
			for (int j = 0; j < shot_num2; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = _x;
					bul[a].y = _y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 2.0f + j * 0.5f;
					bul[a].ang = Define::PI * 2.0f / shot_num1 * i + rang + count / 31.0f + j * 0.03f;
					bul[a].knd = 13;
					bul[a].col = i % 4;
					bul[a].till = 180;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 1;
				}
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}
	if (count % 6 == 0 && count % 600 >= 300 && count % 600 < 540) {
		for (int i = 0; i < shot_num1; i++) {
			for (int j = 0; j < shot_num2; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = _x;
					bul[a].y = _y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 2.0f + j * 0.5f;
					bul[a].ang = Define::PI * 2.0f / shot_num1 * i + rang - count / 31.0f - j * 0.03f;
					bul[a].knd = 13;
					bul[a].col = i % 4 + 4;
					bul[a].till = 180;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 1;
				}
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}
	/*
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			
		}
	}
	*/
	move_bull();
}

//OK
void Enemy::enemy_pattern0006(float px, float py) {
	if (count == 0) {
		time = 45;
		hp_max = 45000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}
	back_tex = 2;
	int shot_count, shot_num;
	switch (level) {
	case 0:
		shot_count = 360;
		shot_num = 3;
		break;
	case 1:
		shot_count = 240;
		shot_num = 4;
		break;
	case 2:
		shot_count = 180;
		shot_num = 5;
		break;
	default:
		shot_count = 600;
		shot_num = 1;
		break;
	}
	int a;
	static int num[4];
	if (count == 0) for (int i = 0; i < 4; i++) num[i] = -1;

	if (count % 120 == 0 && count >= 120) move(90);

	if (count % shot_count == 0) {
		if ((a = search_bull()) >= 0) {
			bul[a].fl = 3;
			bul[a].x = _x;
			bul[a].y = _y;
			bul[a].vx = 0.0f;
			bul[a].vy = 0.0f;
			bul[a].spd = 2.0f;
			bul[a].ang = atan2f(py - _y, px - _x);
			bul[a].knd = 11;
			bul[a].col = 3;
			bul[a].till = 10;
			bul[a].grz = 1;
			bul[a].cnt = 0;
			bul[a].sta = GetRand(62831);
		}
		for (int i = 0; i < 4; i++) {
			if (num[i] < 0) {
				num[i] = a;
				break;
			}
		}
		DxLib::PlaySoundMem(sound_shot2, DX_PLAYTYPE_BACK);
	}

	for (int i = 0; i < 4; i++) {
		if (num[i] >= 0 && bul[num[i]].fl == 3) {
			if (bul[num[i]].cnt >= 60 && count % 8 == 0) {
				if (bul[num[i]].x > -10 && bul[num[i]].x < Define::OUT_W + 10 && bul[num[i]].y > -10 && bul[num[i]].y < Define::OUT_H + 10) {
					for (int j = 0; j < shot_num; j++) {
						if ((a = search_bull()) >= 0) {
							bul[a].fl = 1;
							bul[a].x = bul[num[i]].x;
							bul[a].y = bul[num[i]].y;
							bul[a].vx = 0.0f;
							bul[a].vy = 0.0f;
							bul[a].spd = 4.0f;
							bul[a].ang = Define::PI * 2.0f * j / shot_num + count / 33.0f + bul[num[i]].sta / 10000.0f;
							bul[a].knd = 13;
							bul[a].col = GetRand(7);
							bul[a].till = 10;
							bul[a].grz = 1;
							bul[a].cnt = 0;
							bul[a].sta = 0;
						}
					}
					DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
				}
				else num[i] = -1;
			}
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0007(float px, float py) {
	if (count == 0) {
		time = 30;
		hp_max = 30000;
		hp = hp_max;
		flag = 1;
		change = 0;
		move_flag = 2;

		_x = (float)Define::CENTER_X;
		_y = 150.0f;
	}

	int shot_count;
	switch (level) {
	case 0:
		shot_count = 4;
		break;
	case 1:
		shot_count = 2;
		break;
	case 2:
		shot_count = 1;
		break;
	default:
		shot_count = 10;
		break;
	}
	
	int a;

	if (count % 300 == 210) move(60);

	if (count % shot_count == 0) {
		for (int i = 0; i < 4; i++) {
			if ((a = search_bull()) >= 0) {
				bul[a].fl = 1;
				bul[a].x = _x;
				bul[a].y = _y;
				bul[a].vx = 0.0f;
				bul[a].vy = 0.0f;
				bul[a].spd = 1.5f + GetRand(400) / 100.0f;
				bul[a].ang = GetRand(62831) / 10000.0f;
				bul[a].knd = 18;
				bul[a].col = GetRand(1);
				bul[a].till = 0;
				bul[a].grz = 1;
				bul[a].cnt = 0;
				bul[a].sta = 0;
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0008(float px, float py) {
	if (count == 0) {
		time = 45;
		hp_max = 50000;
		hp = hp_max;
		flag = 1;
		change = 3;
		move_flag = 1;
	}
	back_tex = 3;
	int shot_num1, shot_num2;
	switch (level) {
	case 0:
		shot_num1 = 8;
		shot_num2 = 3;
		break;
	case 1:
		shot_num1 = 12;
		shot_num2 = 3;
		break;
	case 2:
		shot_num1 = 16;
		shot_num2 = 4;
		break;
	default:
		shot_num1 = 4;
		shot_num2 = 1;
		break;
	}
	int a;
	static int num[50];

	if (count % 600 == 0) {
		for (int i = 0; i < 50; i++) num[i] = -1;
		float rang = GetRand(62831) / 10000.0f;
		for (int i = 0; i < shot_num1; i++) {
			if ((a = search_bull()) >= 0) {
				bul[a].fl = 3;
				bul[a].x = _x;
				bul[a].y = _y;
				bul[a].vx = 0.0f;
				bul[a].vy = 0.0f;
				bul[a].spd = 7.0f;
				bul[a].ang = Define::PI * 2.0f / shot_num1 * i + rang;
				bul[a].knd = 5;
				bul[a].col = 5;
				bul[a].till = 600;
				bul[a].grz = 1;
				bul[a].cnt = 0;
				bul[a].sta = 0;
			}
			num[i] = a;
		}
		DxLib::PlaySoundMem(sound_shot2, DX_PLAYTYPE_BACK);
	}
	if (count % 600 == 120) {
		for (int i = 0; i < 50; i++) {
			if (bul[num[i]].fl == 3) {
				if ((a = search_lazer()) != -1) {
					laz[a].col = 0;//íeÇÃêF
					laz[a].knd = 0;//íeÇÃéÌóﬁ
					laz[a].startpt.x = bul[num[i]].x;//ï`âÊÇµénÇﬂÇÈç¿ïW
					laz[a].startpt.y = bul[num[i]].y;
					laz[a].ang = atan2f(py - laz[a].startpt.y, px - laz[a].startpt.x);//äpìx
					laz[a].fl = 1;//ï\é¶Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
					laz[a].cnt = 0;
					laz[a].haba = 1.0f;//ïù
					laz[a].sta = 0;//
					laz[a].length = hypotf(px - laz[a].startpt.x, py - laz[a].startpt.y) + 30.0f;//í∑Ç≥
					laz[a].hantei = 0;//Ç†ÇΩÇËîªíËÇÇ∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
					laz[a].lphy.conv_flag = 0;//âÒì]Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
					laz[a].lphy.conv_base_x = _x;//âÒì]ÇÃäÓèÄÇ∆Ç»ÇÈç¿ïW
					laz[a].lphy.conv_base_y = _y;
					laz[a].lphy.conv_x = laz[a].startpt.x;//âÒì]Ç∑ÇÈÉåÅ[ÉUÅ[ÇÃà íu
					laz[a].lphy.conv_y = laz[a].startpt.y;
					input_lphy(&laz[a], 10, 0.0f);
				}
			}
		}
		DxLib::PlaySoundMem(sound_lazer, DX_PLAYTYPE_BACK);
	}
	if (count % 600 >= 180 && count % 600 < (level == 2 ? 420 : 360)) {
		if (count % 30 == 0) {
			for (int i = 0; i < 50; i++) {
				if (bul[num[i]].fl == 3) {
					for (int j = 0; j < shot_num2; j++) {
						if ((a = search_bull()) >= 0) {
							bul[a].fl = 1;
							bul[a].x = bul[num[i]].x;
							bul[a].y = bul[num[i]].y;
							bul[a].spd = 0.0f;
							bul[a].ang = GetRand(62831) / 10000.0f;
							bul[a].vx = 1.5f * cosf(bul[a].ang);
							bul[a].vy = 1.5f * sinf(bul[a].ang);
							bul[a].knd = GetRand(2) == 0 ? 2 : 14;
							bul[a].col = GetRand(2) == 0 ? 0 : 7;
							bul[a].till = 0;
							bul[a].grz = 1;
							bul[a].cnt = 0;
							bul[a].sta = 1;
						}
					}
				}
			}
			DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
		}
	}

	for (int i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl > 0) {
			if (laz[i].cnt == 60) {
				laz[i].haba = 10.0f;
				laz[i].hantei = 0.5f;
			}
			if (laz[i].cnt == 300) {
				laz[i].fl = 0;
			}
		}
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl == 1 && bul[i].sta == 1) {
			bul[i].ang += Define::PI / 30.0f;
		}
		else if (bul[i].fl == 3) {
			if (bul[i].cnt >= 540) bul[i].spd = 2.0f;
			else if (bul[i].x <= Define::IN_X || bul[i].x >= Define::OUT_W - Define::IN_X || bul[i].y <= Define::IN_Y || bul[i].y >= Define::OUT_H - Define::IN_Y) bul[i].spd = 0.0f;
		}
	}

	lazer_calc();
	move_bull();
}

//OK
void Enemy::enemy_pattern0009(float px, float py) {
	if (flag == 0) {
		time = 40 + level * 10;
		hp_max = 100000;
		hp = hp_max;
		flag = 2;
		count = 0;
		change = 1;
		move_flag = 1;
	}

	int shot_num[4];
	switch (level) {
	case 0:
		shot_num[0] = 4;
		shot_num[1] = 3;
		shot_num[2] = 3;
		shot_num[3] = 1;
		break;
	case 1:
		shot_num[0] = 5;
		shot_num[1] = 5;
		shot_num[2] = 5;
		shot_num[3] = 1;
		break;
	case 2:
		shot_num[0] = 7;
		shot_num[1] = 8;
		shot_num[2] = 8;
		shot_num[3] = 2;
		break;
	default:
		shot_num[0] = 1;
		shot_num[1] = 1;
		shot_num[2] = 1;
		shot_num[3] = 1;
		break;
	}
	int a;
	static int num = 0;
	if (count == 0) num = 0;

	if (count % 600 <= 120) {
		const int t = count % 600, status = count / 600 + 1;
		if (status == 1) {
			if (t % 2 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = Define::OUT_H - t * Define::OUT_H / 120.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		else if (status == 2) {
			if (t % 2 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = Define::OUT_H - powf(bul[a].x - Define::CENTER_X, 2.0f) * 0.006f - 10.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		else if (status == 3) {
			if (t % 3 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = Define::IN_H / 2.0f * -sinf(t * Define::PI / 30.0f) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f - Define::OUT_W;
					bul[a].y = Define::IN_H / 2.0f * -sinf(t * Define::PI / 30.0f) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 300;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		else if (status == 4) {
			if (t % 2 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = Define::CENTER_X * cosf(t * Define::PI / 60.0f * 3) + Define::CENTER_X;
					bul[a].y = Define::CENTER_X * sinf(t * Define::PI / 60.0f * 2) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		else if (status == 5) {
			if (t % 3 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = Define::CENTER_Y * expf(-powf(Define::CENTER_X - bul[a].x, 2.0f) / 20000.0f) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = Define::CENTER_Y * -expf(-powf(Define::CENTER_X - bul[a].x, 2.0f) / 20000.0f) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		else if (status == 6) {
			if (count % 3 <= 1) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * 5.0f * cosf(t * Define::PI / 10.0f) + Define::CENTER_X;
					bul[a].y = t * 5.0f * sinf(t * Define::PI / 10.0f) + Define::CENTER_Y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 0;
					bul[a].col = 1;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = status;
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
	}

	for (int i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl >= 0) {
			if (laz[i].cnt == 60) {
				laz[i].haba = 10.0f;
				laz[i].hantei = 0.5f;
			}
			if (laz[i].cnt == 240) {
				laz[i].fl = 0;
			}
		}
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].sta > 0 && bul[i].sta < 10) {
				if (count % 600 == 180) {
					switch (bul[i].sta) {
					case 1:
						bul[i].vy = (Define::CENTER_Y - bul[i].y) / 30.0f;
						break;
					case 2:
						bul[i].vx = (Define::CENTER_X - bul[i].x) / 30.0f;
						break;
					case 3:
						bul[i].vx = Define::OUT_W / 60.0f;
						break;
					case 4:
						bul[i].vx = (Define::CENTER_X - bul[i].x) / 30.0f;
						bul[i].vy = (Define::CENTER_Y - bul[i].y) / 30.0f;
						break;
					case 5:
						if (bul[i].y < Define::CENTER_Y) bul[i].vy = (Define::CENTER_Y / 2 - bul[i].y) / 30.0f;
						else bul[i].vy = (Define::CENTER_Y * 3 / 2 - bul[i].y) / 30.0f;
						break;
					case 6:
						break;
					default:
						break;
					}
				}
				if (count % 600 == 240) {
					bul[i].vx = bul[i].vy = 0;
					if (bul[i].sta == 3) {
						if (bul[i].x > Define::OUT_W + 1) bul[i].fl = 0;
					}
				}
				if (count % 600 == 300) {
					if (bul[i].y < Define::CENTER_Y) {
						if (bul[i].x > Define::CENTER_X) { //èt
							float rang = GetRand(62831) / 10000.0f;
							for (int j = 0; j < shot_num[0]; j++) {
								if ((a = search_bull()) >= 0) {
									bul[a].fl = 3;
									bul[a].x = bul[i].x;
									bul[a].y = bul[i].y;
									bul[a].vx = 0.0f;
									bul[a].vy = 0.0f;
									bul[a].spd = 1.0f;
									bul[a].ang = Define::PI * 2.0f * j / shot_num[0] + rang;
									bul[a].knd = 1;
									bul[a].col = 2;
									bul[a].till = 0;
									bul[a].grz = 1;
									bul[a].cnt = 0;
									bul[a].sta = 11;
								}
							}
						}
						else { //âƒ
							float rang = GetRand(62831) / 10000.0f;
							for (int j = 0; j < shot_num[1]; j++) {
								if ((a = search_bull()) >= 0) {
									bul[a].fl = 3;
									bul[a].x = bul[i].x;
									bul[a].y = bul[i].y;
									bul[a].vx = 0.0f;
									bul[a].vy = 0.0f;
									bul[a].spd = 1.0f;
									bul[a].ang = Define::PI * 2.0f * j / shot_num[1] + rang;
									bul[a].knd = 9;
									bul[a].col = 5;
									bul[a].till = 0;
									bul[a].grz = 1;
									bul[a].cnt = 0;
									bul[a].sta = 12;
								}
							}
						}
					}
					else {
						if (bul[i].x < Define::CENTER_X) { //èH
							for (int j = 0; j < shot_num[2]; j++) {
								if ((a = search_bull()) >= 0) {
									bul[a].fl = 3;
									bul[a].x = bul[i].x;
									bul[a].y = bul[i].y;
									bul[a].vx = 0.0f;
									bul[a].vy = 0.0f;
									bul[a].spd = 1.0f;
									bul[a].ang = Define::PI * 2.0f * j / shot_num[2] + (count + GetRand(20)) / 100.0f;
									bul[a].knd = 15;
									bul[a].col = 3;
									bul[a].till = 0;
									bul[a].grz = 1;
									bul[a].cnt = 0;
									bul[a].sta = 13;
								}
							}
						}
						else { //ì~
							for (int j = 0; j < shot_num[3]; j++) {
								if ((a = search_lazer()) != -1) {
									laz[a].col = 0;//íeÇÃêF
									laz[a].knd = 1;//íeÇÃéÌóﬁ
									laz[a].startpt.x = bul[i].x;//ï`âÊÇµénÇﬂÇÈç¿ïW
									laz[a].startpt.y = bul[i].y;
									laz[a].ang = GetRand(62831) / 10000.0f;//äpìx
									laz[a].fl = 1;//ï\é¶Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
									laz[a].cnt = 0;
									laz[a].haba = 1.0f;//ïù
									laz[a].sta = 0;//
									laz[a].length = 1200.0f;//í∑Ç≥
									laz[a].hantei = 0;//Ç†ÇΩÇËîªíËÇÇ∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
									laz[a].lphy.conv_flag = 0;//âÒì]Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
									laz[a].lphy.conv_base_x = _x;//âÒì]ÇÃäÓèÄÇ∆Ç»ÇÈç¿ïW
									laz[a].lphy.conv_base_y = _y;
									laz[a].lphy.conv_x = laz[a].startpt.x;//âÒì]Ç∑ÇÈÉåÅ[ÉUÅ[ÇÃà íu
									laz[a].lphy.conv_y = laz[a].startpt.y;
									input_lphy(&laz[a], 10, 0.0f);
								}
							}
						}
					}
					bul[i].fl = 0;
				}
			}
			else if (bul[i].sta == 11) {
				if (bul[i].cnt == 60) bul[i].spd = 0.0f;
				if (bul[i].cnt >= 90 && bul[i].cnt < 120) {
					bul[i].spd += 0.1f;
					bul[i].ang -= Define::PI * 2.0f / 3.0f / 30.0f;
				}
			}
			else if (bul[i].sta == 12) {
				if (bul[i].cnt == 60) bul[i].spd = 0.0f;
				if (bul[i].cnt == 120) {
					bul[i].spd = 2.5f;
					bul[i].ang = atan2f(py - bul[i].y, px - bul[i].x);
				}
			}
			else if (bul[i].sta == 13) {
			if (bul[i].cnt < 60) bul[i].spd += 2.0f / 60.0f;
			}
		}
	}

	lazer_calc();
	move_bull();
	DrawLine(0, Define::CENTER_Y - 1, Define::OUT_W, Define::CENTER_Y - 1, GetColor(0, 255, 255), 3);
	DrawLine(Define::CENTER_X - 1, 0, Define::CENTER_X - 1, Define::OUT_H, GetColor(0, 255, 255), 3);
}

//OK
void Enemy::enemy_pattern0010(float px, float py) {
	if (count == 0) {
		time = 120;
		hp_max = 100000;
		hp = hp_max;
		flag = 2;
		change = 0;
		move_flag = 0;
	}

	int shot_count[4], shot_num[4];
	switch (level) {
	case 0:
		shot_count[0] = 60;
		shot_count[1] = 150;
		shot_count[2] = 300;
		shot_count[3] = 300;
		shot_num[0] = 5;
		shot_num[1] = 8;
		shot_num[2] = 2;
		shot_num[3] = 4;
		break;
	case 1:
		shot_count[0] = 50;
		shot_count[1] = 120;
		shot_count[2] = 240;
		shot_count[3] = 420;
		shot_num[0] = 6;
		shot_num[1] = 12;
		shot_num[2] = 4;
		shot_num[3] = 6;
		break;
	case 2:
		shot_count[0] = 30;
		shot_count[1] = 90;
		shot_count[2] = 180;
		shot_count[3] = 540;
		shot_num[0] = 8;
		shot_num[1] = 24;
		shot_num[2] = 7;
		shot_num[3] = 8;
		break;
	default:
		shot_count[0] = 300;
		shot_count[1] = 120;
		shot_count[2] = 600;
		shot_count[3] = 60;
		shot_num[0] = 3;
		shot_num[1] = 4;
		shot_num[2] = 1;
		shot_num[3] = 2;
		break;
	}

	float laz_haba = 150.0f;
	if (hp <= hp_max * 2 / 3 || time < 90) laz_haba = 200.0f;
	int a;
	static float lazx, lazy;
	
	if (count == 0) {
		for (int i = 0; i < 4; i++) {
			fam[i].fl = 11;
			fam[i].x = _x;
			fam[i].y = _y;
			fam[i].vx = 0.0f;
			fam[i].vy = 0.0f;
			fam[i].ang = -Define::PI / 2.0f;
			fam[i].spd = 0.0f;
			fam[i].hp = hp_max;
			fam[i].ran = 50.0f;
			fam[i].dmg = 0;
			fam[i].cnt = 0;
			fam[i].knd = 1;
			fam[i].img = i + 1;
			fam[i].sta = i;
		}
	}

	if (count >= 120) {
		if (count % shot_count[0] == 0) {
			float rang = GetRand(62831) / 10000.0f;
			for (int i = 0; i < shot_num[0]; i++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].ang = Define::PI * 2.0f * i / shot_num[0] + rang;
					bul[a].x = fam[0].x + cosf(bul[a].ang) * 15.0f;
					bul[a].y = fam[0].y + sinf(bul[a].ang) * 15.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].knd = 15;
					bul[a].col = 2;
					bul[a].till = 100;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 10;
				}
				if (hp <= hp_max * 2 / 3 || time < 90) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 1;
						bul[a].ang = Define::PI * 2.0f * i / shot_num[0] + Define::PI / shot_num[0] + rang;
						bul[a].x = fam[0].x + cosf(bul[a].ang) * 30.0f;
						bul[a].y = fam[0].y + sinf(bul[a].ang) * 30.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 0.0f;
						bul[a].knd = 15;
						bul[a].col = 2;
						bul[a].till = 100;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = 11;
					}
				}
				if (hp <= hp_max / 3 || time < 60) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 1;
						bul[a].ang = 0.0f;
						bul[a].x = fam[0].x + cosf(bul[a].ang) * 30.0f;
						bul[a].y = fam[0].y + sinf(bul[a].ang) * 30.0f;
						bul[a].vx = GetRand(400) / 100.0f - 2.0f;
						bul[a].vy = -GetRand(300) / 100.0f - 3.0f;
						bul[a].spd = 0.0f;
						bul[a].knd = 1;
						bul[a].col = 2;
						bul[a].till = 180;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = 12;
					}
				}
			}
			DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
		}
		if (count % shot_count[1] == 0) {
			float rang = GetRand(62831) / 10000.0f;
			for (int i = 0; i < shot_num[1]; i++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = fam[1].x;
					bul[a].y = fam[1].y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.5f;
					bul[a].ang = Define::PI * 2.0f * i / shot_num[1] + rang;
					bul[a].knd = 9;
					bul[a].col = 4;
					bul[a].till = 300;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 20;
				}
			}
			if (hp <= hp_max * 2 / 3 || time < 90) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = fam[1].x;
					bul[a].y = fam[1].y;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 0.0f;
					bul[a].ang = 0.0f;
					bul[a].knd = 11;
					bul[a].col = 3;
					bul[a].till = 0;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = 21;
				}
			}
			if (hp <= hp_max / 3 || time < 60) {
				for (int i = 0; i < shot_num[1]; i++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 1;
						bul[a].x = fam[1].x;
						bul[a].y = fam[1].y;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.5f;
						bul[a].ang = Define::PI * 2.0f * i / shot_num[1] + rang;
						bul[a].knd = 9;
						bul[a].col = 4;
						bul[a].till = 300;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = 22;
					}
				}
			}
			DxLib::PlaySoundMem(sound_shot2, DX_PLAYTYPE_BACK);
		}
		if (count % shot_count[2] >= 0 && count % shot_count[2] < 120) {
			if (count % shot_count[2] == 0) fam[2].sta = GetRand(62831);
			int way = (count % (shot_count[2] * 2) < shot_count[2] ? 1 : -1);
			if (hp <= hp_max * 2 / 3 || time < 90) shot_num[2]++;
			if (hp <= hp_max / 3 || time < 60) shot_num[2]++;
			if (count % 8 == 0) {
				for (int i = 0; i < shot_num[2]; i++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 1;
						bul[a].x = fam[2].x;
						bul[a].y = fam[2].y;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 5.0f;
						bul[a].ang = Define::PI * 2.0f * i / shot_num[2] + way * count / 27.0f + fam[2].sta / 10000.0f;
						bul[a].knd = 13;
						bul[a].col = GetRand(7);
						bul[a].till = 0;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = 0;
						if (hp <= hp_max / 3 || time < 60) {
							if (way == 1) bul[a].sta = 30;
							else bul[a].sta = 31;
						}
					}
				}
				DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
			}
		}
		if (count % 600 == 0) {
			lazx = px;
			lazy = py;
			if ((a = search_lazer()) != -1) {
				laz[a].col = 0;//íeÇÃêF
				laz[a].knd = 0;//íeÇÃéÌóﬁ
				laz[a].startpt.x = fam[3].x;//ï`âÊÇµénÇﬂÇÈç¿ïW
				laz[a].startpt.y = fam[3].y;
				laz[a].ang = atan2f(lazy - laz[a].startpt.y, lazx - laz[a].startpt.x);//äpìx
				laz[a].fl = 1;//ï\é¶Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
				laz[a].cnt = 0;
				laz[a].haba = 5.0f;//ïù
				laz[a].sta = 0;//
				laz[a].length = 1200.0f;//í∑Ç≥
				laz[a].hantei = 0;//Ç†ÇΩÇËîªíËÇÇ∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
				laz[a].lphy.conv_flag = 0;//âÒì]Ç∑ÇÈÇ©Å@0:ÇµÇ»Ç¢Å@1:Ç∑ÇÈ
				laz[a].lphy.conv_base_x = _x;//âÒì]ÇÃäÓèÄÇ∆Ç»ÇÈç¿ïW
				laz[a].lphy.conv_base_y = _y;
				laz[a].lphy.conv_x = laz[a].startpt.x;//âÒì]Ç∑ÇÈÉåÅ[ÉUÅ[ÇÃà íu
				laz[a].lphy.conv_y = laz[a].startpt.y;
				input_lphy(&laz[a], 10, 0.0f);
			}
			DxLib::PlaySoundMem(sound_lazer, DX_PLAYTYPE_BACK);
		}
	}


	for (int i = 0; i < SHIKI_MAX; i++) {
		if (fam[i].fl >= 1) {
			fam[i].x = _x + 300.0f * cosf(Define::PI * count / 240.0f - Define::PI * (fam[i].img - 1) / 2.0f);
			fam[i].y = _y + 100.0f * sinf(Define::PI * count / 240.0f - Define::PI * (fam[i].img - 1) / 2.0f);
			hp -= fam[i].dmg;
		}
	}

	for (int i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl >= 1) {
			laz[i].startpt.x = fam[3].x;
			laz[i].startpt.y = fam[3].y;
			laz[i].ang = atan2f(lazy - laz[i].startpt.y, lazx - laz[i].startpt.x);
			if (laz[i].cnt >= 60 && laz[i].cnt <= 180) {
				if (laz[i].cnt == 90) laz[i].hantei = 0.6f;
				laz[i].haba = laz_haba / 120.0f * (laz[i].cnt - 60.0f) + 5.0f;
			}
			if (laz[i].cnt >= shot_count[3] - 60 && laz[i].cnt < shot_count[3]) {
				if (laz[i].cnt == shot_count[3] - 20) laz[i].hantei = 0;
				laz[i].haba = laz_haba / 60.0f * (shot_count[3] - laz[i].cnt);
			}
			if (hp <= hp_max / 3 || time < 60) {
				if (laz[i].cnt >= 120 && laz[i].cnt < shot_count[3] - 60) {
					if (laz[i].cnt % 10 == 0) {
						for (int j = 0; j < shot_num[3]; j++) {
							if ((a = search_bull()) >= 0) {
								bul[a].fl = 1;
								bul[a].x = laz[i].startpt.x;
								bul[a].y = laz[i].startpt.y;
								bul[a].spd = 0.0f;
								bul[a].ang = GetRand(62831) / 6.0f / 10000.0f - Define::PI / 6.0f + laz[i].ang;
								bul[a].vx = 4.0f * cosf(bul[a].ang);
								bul[a].vy = 4.0f * sinf(bul[a].ang);
								bul[a].knd = 14;
								bul[a].col = GetRand(2) == 0 ? 0 : 7;
								bul[a].till = 0;
								bul[a].grz = 1;
								bul[a].cnt = 0;
								bul[a].sta = 40;
							}
						}
					}
				}
			}
			if (laz[i].cnt == shot_count[3]) laz[i].fl = 0;
		}
	}
	
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			switch (bul[i].sta) {
			case 10:
				if (bul[i].cnt >= 180 && bul[i].cnt < 210) bul[i].spd += 0.13f;
				break;

			case 11:
				if (bul[i].cnt >= 180 && bul[i].cnt < 210) bul[i].spd += 0.09f;
				break;

			case 12:
				if (bul[i].cnt <= 240) bul[i].vy += 0.04f;
				bul[i].ang = atan2f(bul[i].vy, bul[i].vx);
				break;

			case 20:
				if (bul[i].cnt == 90) bul[i].spd = 0.0f;
				if (bul[i].cnt == 180) {
					bul[i].spd = 2.0f;
					bul[i].ang = atan2f(py - bul[i].y, px - bul[i].x);
				}
				break;

			case 21:
				if (bul[i].cnt == 180) {
					bul[i].spd = 2.0f;
					bul[i].ang = atan2f(py - bul[i].y, px - bul[i].x);
				}
				break;
				
			case 22:
				if (bul[i].cnt == 90) bul[i].spd = 0.0f;
				if (bul[i].cnt == 180) bul[i].ang += Define::PI;
				if (bul[i].cnt >= 180 && bul[i].cnt < 210) bul[i].spd += 0.15f;
				break;

			case 30:
				if (bul[i].cnt >= 30) bul[i].ang += 0.007f;
				break;

			case 31:
				if (bul[i].cnt >= 30) bul[i].ang -= 0.007f;
				break;

			case 40:
				bul[i].ang += Define::PI / 30.0f;
				break;

			default:
				break;
			}
		}
	}

	lazer_calc();
	move_bull();
}
