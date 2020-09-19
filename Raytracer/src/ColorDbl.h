#pragma once
#include "Includer.h"

class ColorDbl {
public:
	ColorDbl() = default;
	ColorDbl(double r, double g, double b) 
		:color{r,g,b} {}

private:
	glm::vec3 color;
};