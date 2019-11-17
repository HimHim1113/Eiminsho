#include "Enemy.h"
#include <DxLib.h>
#include <cmath>
#include "Define.h"


//OK
void Enemy::enemy_pattern0000(float px, float py) {
	if (count == 0) {
		time = 40;
		hp_max = 40000;
		hp = hp_max;
		flag = 1;
		change = 0;
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
		time = 40;
		hp_max = 35000;
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
		time = 50;
		hp_max = 60000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}
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
				bul[a].grz = 1;
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
		time = 40;
		hp_max = 40000;
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
			fam[a].img = 1;
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
		time = 50;
		hp_max = 60000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}

	int shot_num;
	switch (level) {
	case 0:
		shot_num = 16;
		break;
	case 1:
		shot_num = 30;
		break;
	case 2:
		shot_num = 56;
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
			fam[a].img = 1;
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
		time = 40;
		hp_max = 40000;
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

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			
		}
	}

	move_bull();
}

//OK
void Enemy::enemy_pattern0006(float px, float py) {
	if (count == 0) {
		time = 50;
		hp_max = 55000;
		hp = hp_max;
		flag = 1;
		change = 1;
		move_flag = 1;
	}

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
		time = 40;
		hp_max = 40000;
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
		time = 50;
		hp_max = 60000;
		hp = hp_max;
		flag = 1;
		change = 3;
		move_flag = 1;
	}

	int shot_num1, shot_num2;
	switch (level) {
	case 0:
		shot_num1 = 12;
		shot_num2 = 2;
		break;
	case 1:
		shot_num1 = 20;
		shot_num2 = 2;
		break;
	case 2:
		shot_num1 = 20;
		shot_num2 = 3;
		break;
	default:
		shot_num1 = 8;
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
					laz[a].col = 0;//弾の色
					laz[a].knd = 1;//弾の種類
					laz[a].startpt.x = bul[num[i]].x;//描画し始める座標
					laz[a].startpt.y = bul[num[i]].y;
					laz[a].ang = atan2f(py - laz[a].startpt.y, px - laz[a].startpt.x);//角度
					laz[a].fl = 1;//表示するか　0:しない　1:する
					laz[a].cnt = 0;
					laz[a].haba = 1.0f;//幅
					laz[a].sta = 0;//
					laz[a].length = hypotf(px - laz[a].startpt.x, py - laz[a].startpt.y) + 30.0f;//長さ
					laz[a].hantei = 0;//あたり判定をするか　0:しない　1:する
					laz[a].lphy.conv_flag = 0;//回転するか　0:しない　1:する
					laz[a].lphy.conv_base_x = _x;//回転の基準となる座標
					laz[a].lphy.conv_base_y = _y;
					laz[a].lphy.conv_x = laz[a].startpt.x;//回転するレーザーの位置
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

//
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

	int shot_count, shot_num;
	switch (level) {
	case 0:
		shot_count = 10;
		shot_num = 0;
		break;
	case 1:
		shot_count = 5;
		shot_num = 4;
		break;
	case 2:
		shot_count = 3;
		shot_num = 6;
		break;
	case 3:
		shot_count = 2;
		shot_num = 8;
		break;
	default:
		shot_count = 30;
		shot_num = 2;
		break;
	}
	int a;
	static int num = 0;
	if (count == 0) num = 0;

	if (count % 600 <= 120) {
		const int t = count % 600, status = count / 600 + 1;
		if (status == 1) {
			if (t % 5 == 0) {
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
			}
		}
		else if (status == 2) {
			if (t % 3 == 0) {
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
			}
		}
		else if (status == 3) {
			if (t % 2 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = t * Define::OUT_W / 120.0f;
					bul[a].y = 300.0f * -sinf(t * Define::PI / 30.0f) + Define::CENTER_Y;
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
			}
		}
		else if (status == 4) {
			if (t % 3 == 0) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = 300.0f * cosf(t * Define::PI / 60.0f) + Define::CENTER_X;
					bul[a].y = 300.0f * -sinf(t * Define::PI / 60.0f) + Define::CENTER_Y;
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
			}
		}
		else if (status == 6) {

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
						bul[i].vx = (Define::CENTER_X - bul[i].x) / 30.0f;
						bul[i].vy = (Define::CENTER_Y - bul[i].y) / 30.0f;
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
				}
				if (count % 600 == 300) {
					bul[i].spd = GetRand(100) / 100.0f + 1.0f;
					bul[i].ang = GetRand(62831) / 10000.0f;
					bul[i].sta = 10;
				}
			}
			else if (bul[i].sta == 11) {

			}
			else if (bul[i].sta == 12) {

			}
			else if (bul[i].sta == 13) {

			}
		}
	}

	lazer_calc();
	move_bull();
	DrawLine(0, Define::CENTER_Y - 1, Define::OUT_W, Define::CENTER_Y - 1, GetColor(0, 255, 255), 3);
	DrawLine(Define::CENTER_X - 1, 0, Define::CENTER_X - 1, Define::OUT_H, GetColor(0, 255, 255), 3);
}

//
void Enemy::enemy_pattern0010(float px, float py) {
	if (count == 0) {
		time = 99;
		hp_max = 80000;
		hp = hp_max;
		flag = 1;
		change = 5;
		move_flag = 1;
	}

	if (count % 210 == 0) move(60);
	int a;

	if (count % 420 == 0) {
		float ranx = GetRand(Define::IN_W * 10) / 10.0f;
		float rany = GetRand(1000) / 10.0f;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 10; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = (float)Define::CENTER_X;
					bul[a].y = 150.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.5f;
					bul[a].ang = Define::PI * 2.0f * i / 16.0f;
					bul[a].knd = 7;
					bul[a].col = 0;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = (float)Define::CENTER_X;
					bul[a].y = 150.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.5f;
					bul[a].ang = Define::PI * 2.0f * i / 16.0f;
					bul[a].knd = 7;
					bul[a].col = 0;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j + 10;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = Define::CENTER_X - 150.0f;
					bul[a].y = 300.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.0f;
					bul[a].ang = Define::PI * 2.0f * i / 8.0f;
					bul[a].knd = 7;
					bul[a].col = 3;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = Define::CENTER_X + 150.0f;
					bul[a].y = 300.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.0f;
					bul[a].ang = Define::PI * 2.0f * i / 8.0f;
					bul[a].knd = 7;
					bul[a].col = 3;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j + 10;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = Define::CENTER_X - 300.0f;
					bul[a].y = 500.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.0f;
					bul[a].ang = Define::PI * 2.0f * i / 8.0f;
					bul[a].knd = 7;
					bul[a].col = 6;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j + 10;
				}
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 3;
					bul[a].x = Define::CENTER_X + 300.0f;
					bul[a].y = 500.0f;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.0f;
					bul[a].ang = Define::PI * 2.0f * i / 8.0f;
					bul[a].knd = 7;
					bul[a].col = 6;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j;
				}
			}
		}

		if (level >= 2) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X - 200.0f;
						bul[a].y = 150.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 8.0f;
						bul[a].knd = 7;
						bul[a].col = 1;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j;
					}
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X + 200.0f;
						bul[a].y = 150.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 8.0f;
						bul[a].knd = 7;
						bul[a].col = 1;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j + 10;
					}
				}
			}
		}
		if (level == 3) {
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 10; j++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = (float)Define::CENTER_X;
						bul[a].y = 150.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.5f;
						bul[a].ang = Define::PI * 2.0f * i / 16.0f + Define::PI / 16.0f;
						bul[a].knd = 7;
						bul[a].col = 0;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j;
					}
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = (float)Define::CENTER_X;
						bul[a].y = 150.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.5f;
						bul[a].ang = Define::PI * 2.0f * i / 16.0f + Define::PI / 16.0f;
						bul[a].knd = 7;
						bul[a].col = 0;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j + 10;
					}
				}
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X - 150.0f;
						bul[a].y = 300.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 8.0f + Define::PI / 8.0f;
						bul[a].knd = 7;
						bul[a].col = 3;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j;
					}
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X + 150.0f;
						bul[a].y = 300.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 8.0f + Define::PI / 8.0f;
						bul[a].knd = 7;
						bul[a].col = 3;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j + 10;
					}
				}
			}
			float rang = GetRand(62831) / 10000.0f;
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 8; j++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X - 100.0f;
						bul[a].y = 50.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 12.0f + rang;
						bul[a].knd = 7;
						bul[a].col = 4;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j + 10;
					}
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 3;
						bul[a].x = Define::CENTER_X + 100.0f;
						bul[a].y = 50.0f;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f;
						bul[a].ang = Define::PI * 2.0f * i / 12.0f + rang;
						bul[a].knd = 7;
						bul[a].col = 4;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = j;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if ((a = search_bull()) >= 0) {
						bul[a].fl = 1;
						bul[a].x = _x;
						bul[a].y = _y;
						bul[a].vx = 0.0f;
						bul[a].vy = 0.0f;
						bul[a].spd = 1.0f + j * 0.5f;
						bul[a].ang = atan2f(py - _y, px - _x) + Define::PI / 8.0f * (i - 2);
						bul[a].knd = 11;
						bul[a].col = 7;
						bul[a].till = 240;
						bul[a].grz = 1;
						bul[a].cnt = 0;
						bul[a].sta = -1;
					}
				}
			}
		}
		DxLib::PlaySoundMem(sound_shot1, DX_PLAYTYPE_BACK);
	}

	if (count % 60 == 0 && count % 420 >= 180 && count % 420 < 420) {
		float ranx = GetRand(Define::IN_W * 10) / 10.0f + Define::IN_X, rany = GetRand(2000) / 10.0f + 50.0f;
		float rang = GetRand(62831) / 10000.0f;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				if ((a = search_bull()) >= 0) {
					bul[a].fl = 1;
					bul[a].x = ranx;
					bul[a].y = rany;
					bul[a].vx = 0.0f;
					bul[a].vy = 0.0f;
					bul[a].spd = 1.5f;
					bul[a].ang = rang + Define::PI * 2.0f * i / 16.0f;
					bul[a].knd = 19;
					bul[a].col = 4;
					bul[a].till = 240;
					bul[a].grz = 1;
					bul[a].cnt = 0;
					bul[a].sta = j + 100;
				}
			}
		}
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl >= 1) {
			if (bul[i].sta >= 0 && bul[i].sta < 10) {
				if (bul[i].cnt >= 30 && bul[i].cnt < 180) bul[i].ang += Define::PI / 180.0f + bul[i].col / 500.0f;
				if (bul[i].cnt == 180) {
					bul[i].spd = 2.0f + 0.5f * bul[i].sta;
				}
			}
			if (bul[i].sta >= 10 && bul[i].sta < 20) {
				if (bul[i].cnt >= 30 && bul[i].cnt < 180) bul[i].ang -= Define::PI / 180.0f + bul[i].col / 500.0f;
				if (bul[i].cnt == 180) {
					bul[i].spd = 2.0f + 0.5f * (bul[i].sta - 10);
				}
			}
			if (bul[i].sta >= 100) {
				if (bul[i].cnt == 120) {
					bul[i].ang = atan2f(py - bul[i].y, px - bul[i].x);
					bul[i].spd = 2.5f + 0.5f * (bul[i].sta - 100);
				}
			}
		}
	}

	move_bull();
}
