#include "Bullet.h"
#include <cmath>
#include "Define.h"


void Bullet::update_bull() {
	if (fl > 0) {
		x += spd * cosf(ang) + vx;
		y += spd * sinf(ang) + vy;
		cnt++;
		if (x < -50 || x > Define::OUT_W + 50 ||
			x < -50 || y > Define::OUT_H + 50) {//‰æ–Ê‚©‚çŠO‚ê‚½‚ç
			if (till < cnt)//Å’áÁ‚¦‚È‚¢ŽžŠÔ‚æ‚è’·‚¯‚ê‚Î
				fl = 0;//Á‚·
		}
	}
}