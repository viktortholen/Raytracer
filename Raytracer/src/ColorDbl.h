#pragma once
#include "Includer.h"

class ColorDbl {
public:
	ColorDbl() = default;
	ColorDbl(const double &r, const double &g, const double &b) 
		:color{r,g,b} {}
	glm::vec3 getColorVec() {
		return color;
	}
	ColorDbl operator+=(const ColorDbl& c) {
		return ColorDbl(color.r + c.color.r, color.g + c.color.g, color.b + c.color.b);
	}
private:
	glm::vec3 color{0,0,0}; //background is black.
};