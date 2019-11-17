#include "Enemy.h"
#include <cmath>
#include "Define.h"


/* ２次元ベクトル */
typedef struct {
	float x, y;
} Vector2_t;

/* diff ← ベクトル p - q */
void Vector2Diff(Vector2_t* diff, const Vector2_t* p, const Vector2_t* q) {
	diff->x = p->x - q->x;
	diff->y = p->y - q->y;
}

/* ベクトル p と q の内積 */
float Vector2InnerProduct(const Vector2_t* p, const Vector2_t* q) {
	return p->x * q->x + p->y * q->y;
}

/* ベクトル p と q の外積 */
float Vector2OuterProduct(const Vector2_t* p, const Vector2_t* q) {
	return p->x * q->y - p->y * q->x;
}

//点と線分との距離を求める
float get_distance(float x, float y, float x1, float y1,
	float x2, float y2) {
	float dx, dy, a, b, t, tx, ty;
	float distance;
	dx = (x2 - x1); dy = (y2 - y1);
	a = dx * dx + dy * dy;
	b = dx * (x1 - x) + dy * (y1 - y);
	t = -b / a;
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	tx = x1 + dx * t;
	ty = y1 + dy * t;
	distance = sqrt((x - tx) * (x - tx) + (y - ty) * (y - ty));
	return distance;
}

//点と点との距離を返す
float get_pt_and_pt(pt_t p1, pt_t p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//点が円の中にあるかどうか。0:なし　1:あり
float question_point_and_circle(pt_t p, pt_t rp, float r) {
	float dx = p.x - rp.x, dy = p.y - rp.y;
	if (dx * dx + dy * dy < r * r)    return 1;
	else                    return 0;
}

//入れ替え
void swap_float(float* n, float* m) {
	float t = *m;
	*m = *n; *n = t;
}

//３点から角度を返す
float get_sita(pt_t pt0, pt_t pt1, pt_t rpt) {
	/* ベクトル C→P と C→Q のなす角θおよび回転方向を求める．*/
	Vector2_t c, p, q; /* 入力データ */
	Vector2_t cp;      /* ベクトル C→P */
	Vector2_t cq;      /* ベクトル C→Q */
	float s;          /* 外積：(C→P) × (C→Q) */
	float t;          /* 内積：(C→P) ・ (C→Q) */
	float theta;      /* θ (ラジアン) */

	/* c，p，q を所望の値に設定する．*/
	c.x = pt0.x;    c.y = pt0.y;
	p.x = pt1.x;    p.y = pt1.y;
	q.x = rpt.x;    q.y = rpt.y;

	/* 回転方向および角度θを計算する．*/
	Vector2Diff(&cp, &p, &c);          /* cp ← p - c   */
	Vector2Diff(&cq, &q, &c);          /* cq ← q - c   */
	s = Vector2OuterProduct(&cp, &cq); /* s ← cp × cq */
	t = Vector2InnerProduct(&cp, &cq); /* t ← cp ・ cq */
	theta = atan2(s, t);
	return theta;
}

//長方形と円との当たりを判定する
int hitjudge_square_and_circle(pt_t pt[4], pt_t rpt, float r) {
	//int i;
	//float a[4], b[4];//a:傾き　b:y切片
	float x = rpt.x, y = rpt.y;
	float theta, theta2;

	/*円の中に長方形の４点のうちどれかがあるかどうか判定*/
	/*
	for (i = 0; i < 4; i++) {
		if (question_point_and_circle(pt[i], rpt, r) == 1)
			return 1;
	}
	*/
	/*ここまで*/

	/*長方形の中に物体が入り込んでいるかどうかを判定判定*/

	theta = get_sita(pt[0], pt[1], rpt);//3点の成す角1
	theta2 = get_sita(pt[2], pt[3], rpt);//3点の成す角2

	if (0.0f < theta && theta < Define::PI / 2.0f && 0.0f < theta2 && theta2 < Define::PI / 2.0f) 
		return 1;

	/*ここまで*/

	/*線分と点との距離を求める*/
	/*
	for (i = 0; i < 4; i++) {
		if (get_distance(rpt.x, rpt.y, pt[i].x, pt[i].y, pt[(i + 1) % 4].x, pt[(i + 1) % 4].y) < r)
			return 1;
	}
	*/
	/*ここまで*/
	return 0;//どこにもヒットしなかったらぶつかっていない
}


int Enemy::out_lazer(float px, float py) {
	pt_t sqrp[4], rpt = { px, py };//長方形の4点と円の中心
	//レーザー分ループ
	for (int i = 0; i < Enemy::LAZER_MAX; i++) {
		//レーザーが登録されていて、当たり判定をする設定なら
		if (laz[i].fl == 1 && laz[i].hantei > 0) {
			for (int j = 0; j < 4; j++) {//レーザーの4点を設定
				sqrp[j].x = laz[i].outpt[j].x;
				sqrp[j].y = laz[i].outpt[j].y;
			}
			//長方形と円との接触判定
			if (hitjudge_square_and_circle(sqrp, rpt, 1.0f) == 1) return 1;
		}
	}
	return 0;
}


void Enemy::input_lphy(Lazer* laz, int time, float angle) {
	laz->lphy.ang = angle;
	laz->lphy.base_ang = laz->ang;
	laz->lphy.time = (float)time;
}

void Enemy::lazer_calc() {
	int i;
	for (i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl > 0) {
			//表示位置を設定
			laz[i].disppt[0].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * laz[i].haba;
			laz[i].disppt[0].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * laz[i].haba;
			laz[i].disppt[1].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * laz[i].haba;
			laz[i].disppt[1].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * laz[i].haba;
			laz[i].disppt[2].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * laz[i].haba + cos(laz[i].ang) * laz[i].length;
			laz[i].disppt[2].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * laz[i].haba + sin(laz[i].ang) * laz[i].length;
			laz[i].disppt[3].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * laz[i].haba + cos(laz[i].ang) * laz[i].length;
			laz[i].disppt[3].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * laz[i].haba + sin(laz[i].ang) * laz[i].length;
			//あたり範囲を設定
			laz[i].outpt[0].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 10.0f);
			laz[i].outpt[0].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 10.0f);
			laz[i].outpt[1].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 10.0f);
			laz[i].outpt[1].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 10.0f);
			laz[i].outpt[2].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * laz[i].hantei + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[2].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * laz[i].hantei + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[3].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * laz[i].hantei + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[3].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * laz[i].hantei + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);

			float ymax = laz[i].lphy.ang, ty = laz[i].lphy.time, t = (float)laz[i].cnt;
			float delt = ymax / ty * t;
			if (laz[i].lphy.time != 0)//回転移動時間内なら
				laz[i].ang = laz[i].lphy.base_ang + delt;//回転する
			if (laz[i].lphy.conv_flag == 1) {//座標変換をするか
				conv_pos0(&laz[i].startpt.x, &laz[i].startpt.y,
					laz[i].lphy.conv_x, laz[i].lphy.conv_y,
					laz[i].lphy.conv_base_x, laz[i].lphy.conv_base_y,
					-delt);
			}
			if (laz[i].cnt > laz[i].lphy.time) {//回転時間を過ぎるとやめる
				laz[i].lphy.time = 0;
				laz[i].lphy.conv_flag = 0;
			}
			laz[i].cnt++;
		}
	}
}


void Enemy::lazer_calc2() {
	int i;
	for (i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl > 0) {
			//表示位置を設定
			laz[i].disppt[0].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * laz[i].haba;
			laz[i].disppt[0].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * laz[i].haba;
			laz[i].disppt[1].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * laz[i].haba;
			laz[i].disppt[1].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * laz[i].haba;
			laz[i].disppt[2].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * laz[i].haba + cos(laz[i].ang) * laz[i].length;
			laz[i].disppt[2].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * laz[i].haba + sin(laz[i].ang) * laz[i].length;
			laz[i].disppt[3].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * laz[i].haba + cos(laz[i].ang) * laz[i].length;
			laz[i].disppt[3].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * laz[i].haba + sin(laz[i].ang) * laz[i].length;
			//あたり範囲を設定
			laz[i].outpt[0].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 6.0f);
			laz[i].outpt[0].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 6.0f);
			laz[i].outpt[1].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 6.0f);
			laz[i].outpt[1].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) / 6.0f);
			laz[i].outpt[2].x = laz[i].startpt.x + cos(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * laz[i].hantei + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[2].y = laz[i].startpt.y + sin(laz[i].ang - Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * laz[i].hantei + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[3].x = laz[i].startpt.x + cos(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + cos(laz[i].ang) * laz[i].length * laz[i].hantei + cos(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);
			laz[i].outpt[3].y = laz[i].startpt.y + sin(laz[i].ang + Define::PI / 2) * (laz[i].haba * laz[i].hantei) + sin(laz[i].ang) * laz[i].length * laz[i].hantei + sin(laz[i].ang) * laz[i].length * ((1 - laz[i].hantei) * 5.0f / 6.0f);

			float ymax = laz[i].lphy.ang, ty = laz[i].lphy.time, t = (float)laz[i].cnt;
			float delt = (2 * ymax * t / ty - ymax * t * t / (ty * ty));
			if (laz[i].lphy.time != 0)//回転移動時間内なら
				laz[i].ang = laz[i].lphy.base_ang + delt;//回転する
			if (laz[i].lphy.conv_flag == 1) {//座標変換をするか
				conv_pos0(&laz[i].startpt.x, &laz[i].startpt.y,
					laz[i].lphy.conv_x, laz[i].lphy.conv_y,
					laz[i].lphy.conv_base_x, laz[i].lphy.conv_base_y,
					-delt);
			}
			if (laz[i].cnt > laz[i].lphy.time) {//回転時間を過ぎるとやめる
				laz[i].lphy.time = 0;
				laz[i].lphy.conv_flag = 0;
			}
			laz[i].cnt++;
		}
	}
}

//座標回転
//(x0,y0)から(mx,my)を基準にang角回転した角度を(x,y)にいれる
void Enemy::conv_pos0(float* x, float* y, float x0, float y0, float mx, float my, float ang) {
	float ox = x0 - mx, oy = y0 - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}

int Enemy::hit_shot(float cx, float cy) {
	int hit_flag = 0;
	if (flag == 1 && (cx - _x) * (cx - _x) + (cy - _y) * (cy - _y) < 900.0f) hit_flag = 1;
	else {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bul[i].fl == 1 || bul[i].fl == 3) {
				float dx = cx - bul[i].x;
				float dy = cy - bul[i].y;
				//中間を計算する必要があれば
				if (bul[i].spd > hitrange_bullet[bul[i].knd]) {
					//１フレーム前にいた位置を格納する
					float pre_x = bul[i].x + cosf(bul[i].ang + Define::PI) * bul[i].spd;
					float pre_y = bul[i].y + sinf(bul[i].ang + Define::PI) * bul[i].spd;
					float px, py;
					for (int j = 0; j < (int)(bul[i].spd / hitrange_bullet[bul[i].knd]); j++) {//進んだ分÷当たり判定分ループ
						px = pre_x - cx;
						py = pre_y - cy;
						if (px * px + py * py < hitrange_bullet[bul[i].knd] * hitrange_bullet[bul[i].knd]) {
							if (bul[i].fl == 1) bul[i].fl = 0;
							hit_flag = 1;
						}
						pre_x += cosf(bul[i].ang) * hitrange_bullet[bul[i].knd];
						pre_y += sinf(bul[i].ang) * hitrange_bullet[bul[i].knd];
					}
				}
				else if (dx * dx + dy * dy < hitrange_bullet[bul[i].knd] * hitrange_bullet[bul[i].knd]) {
					if (bul[i].fl == 1) bul[i].fl = 0;
					hit_flag = 1;
				}
			}
		}
		if (hit_flag == 0) hit_flag = out_lazer(cx, cy);
	}
	if (hit_flag == 0) {
		for (int i = 0; i < SHIKI_MAX; i++) {
			if (fam[i].fl >= 10) {
				float dx = fam[i].x - cx;
				float dy = fam[i].y - cy;
				if (dx * dx + dy * dy < fam[i].ran * fam[i].ran) {
					hit_flag = 1;
					break;
				}
			}
		}
	}
	return hit_flag;
}

int Enemy::count_graze(float cx, float cy) {
	int graze = 0;
	if (hit_flag == 1) graze = 0;
	else {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bul[i].fl == 1 || bul[i].fl == 3) {
				float dx = cx - bul[i].x;
				float dy = cy - bul[i].y;
				if (dx * dx + dy * dy < (hitrange_bullet[bul[i].knd] + 15.0f) * (hitrange_bullet[bul[i].knd] + 15.0f) && bul[i].grz > 0) {
					bul[i].grz--;
					graze++;
				}
			}
		}
	}
	return graze;
}


int Enemy::search_bull() const {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl == 0) return i;
	}
	return -1;
}

int Enemy::search_bull(int min, int max) const {
	for (int i = min; i < max; i++) {
		if (bul[i].fl == 0) return i;
	}
	return -1;
}

int Enemy::search_lazer() const {
	for (int i = 0; i < LAZER_MAX; i++) {
		if (laz[i].fl == 0) return i;
	}
	return -1;
}

int Enemy::search_shiki() const {
	for (int i = 0; i < SHIKI_MAX; i++) {
		if (fam[i].fl == 0) return i;
	}
	return -1;
}

void Enemy::move_bull() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bul[i].fl > 0) {
			bul[i].x += bul[i].spd * cosf(bul[i].ang) + bul[i].vx;
			bul[i].y += bul[i].spd * sinf(bul[i].ang) + bul[i].vy;
			bul[i].cnt++;
			if (bul[i].x < -50 || bul[i].x > Define::OUT_W + 50 ||
				bul[i].x < -50 || bul[i].y > Define::OUT_H + 50) {//画面から外れたら
				if (bul[i].till < bul[i].cnt)//最低消えない時間より長ければ
					bul[i].fl = 0;//消す
			}
		}
	}
}

void Enemy::update_shiki() {
	for (int i = 0; i < SHIKI_MAX; i++) {
		if (fam[i].fl > 0) {
			fam[i].x += fam[i].spd * cosf(fam[i].ang) + fam[i].vx;
			fam[i].y += fam[i].spd * sinf(fam[i].ang) + fam[i].vy;
			fam[i].cnt++;
			if (fam[i].x < -200 || fam[i].x > Define::OUT_W + 200 ||
				fam[i].y < -200 || fam[i].y > Define::OUT_H + 200) {//画面から外れたら
				fam[i].fl = 0;//消す
			}
		}
	}
}
