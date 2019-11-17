#pragma once

#include <cmath>

class CalcUtils final
{
public:
	CalcUtils() = delete;
	
	static float roundPoint(float val, int point) {
		float ret;
		ret = val * pow(10.f, +point - 1);
		ret = (float)(int)(ret + 0.5f);
		return ret * pow(10.f, -point + 1);
	}
};

