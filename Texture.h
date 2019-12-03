#pragma once

#include "AbstractBack.h"
#include <array>

class Texture final : public AbstractBack
{
public:
	Texture();
	~Texture() = default;
	bool update() override;
	void draw() const override;
	void main(int);

private:
	static const int TEXNUM = 4;

	std::array<int, TEXNUM> tex;
	int num, count;
	float angle;
};
