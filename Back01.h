#pragma once

#include <list>
#include <memory>
#include <array>
#include "Surface.h"
#include "AbstractBack.h"

class Back01 final : public AbstractBack
{

public:
    Back01();
    ~Back01() = default;
	void update(int);
    bool update() override;
    void draw() const override;

private:
	class Quadrangle {
	public:
		const int img;
		float x, y;
		Quadrangle(float x, float y, int img) : x(x), y(y), img(img) {}
	};

	const static int MAX = 4;
	double exrate;
	int img_first, img_second;
	int img[MAX];
	std::array<std::array<std::shared_ptr<Quadrangle>, 2>, MAX> _list;
	int num, count;
};
