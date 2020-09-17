#pragma once

#include "Includer.h"

class Direction {
public:
	Direction() = default;
	Direction(float _x, float _y, float _z)
		:x{ _x }, y{ _y }, z{ _z }{}
	//assignment copy
private:
	float x, y, z;
};