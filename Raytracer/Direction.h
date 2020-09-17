#pragma once

#include "Includer.h"

class Direction {
public:
	Direction() = default;
	Direction(float x, float y, float z)
		:dir{x,y,z} {}
	Direction(glm::vec3 vec)
		:dir{ vec } {}
	//assignment copy
private:
	glm::vec3 dir;
};