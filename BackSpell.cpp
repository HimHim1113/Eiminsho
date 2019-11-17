#include "BackSpell.h"
#include "Define.h"
#include <DxLib.h>

using namespace std;

const static int   IMG_HEIGHT = 879;
const static float SCROLL_SPEED = 2.f;

BackSpell::BackSpell()
{
    _list[0] = make_shared<Quadrangle>(0.f, IMG_HEIGHT * 0.f, LoadGraph("./dat/img/back/01spell/00.png"));
    _list[1] = make_shared<Quadrangle>(0.f, IMG_HEIGHT * 1.f, LoadGraph("./dat/img/back/01spell/01.png"));
    _list[2] = make_shared<Quadrangle>(0.f, IMG_HEIGHT * 2.f, LoadGraph("./dat/img/back/01spell/00.png"));
    _list[3] = make_shared<Quadrangle>(0.f, IMG_HEIGHT * 3.f, LoadGraph("./dat/img/back/01spell/01.png"));
}

bool BackSpell::update()
{
    for (int i = 0; i < NUM; i++) {//�S�ď�ɃX�N���[��������
        _list[i]->y -= SCROLL_SPEED;
        if (_list[i]->y < -IMG_HEIGHT) {//��ɍs���؂�����
            _list[i]->y += IMG_HEIGHT * 4;//��ԉ��ɉ�����
        }
    }
    return true;
}

void BackSpell::draw() const
{
    SetDrawArea(0, 0, Define::OUT_W, Define::OUT_H);    //�G���A�O�͕`��ΏۊO�ɂ���
    for (int i = 0; i < NUM; i++) {
        DrawGraphF(_list[i]->x, _list[i]->y, _list[i]->img, FALSE);
    }
    SetDrawArea(0, 0, Define::WIN_W, Define::WIN_H);    //�`��͈͂����ɖ߂�
}
