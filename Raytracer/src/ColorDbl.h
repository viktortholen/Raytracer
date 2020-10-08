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

	ColorDbl operator*(const float& t) {
		ColorDbl tmp{ *this };
		tmp.color[0] *= t;
		tmp.color[1] *= t;
		tmp.color[2] *= t;
		return tmp;
	}
	ColorDbl operator+=(const ColorDbl& c) {
		ColorDbl tmp{ *this };
		tmp.color[0] += c.color[0];
		tmp.color[1] += c.color[1];
		tmp.color[2] += c.color[2];
		return tmp;
	}
	ColorDbl operator+(const ColorDbl& c) {
		ColorDbl tmp{ *this };
		return tmp += c;
	}	
	ColorDbl operator/(const float& t) {
		ColorDbl tmp{ *this };
		tmp.color[0] /= t;
		tmp.color[1] /= t;
		tmp.color[2] /= t;
		return tmp;
	}
	void printCoords()
	{
		std::cout << "\nr: " << color[0] << ", g: " << color[1] << " , b: " << color[2];
	}

	//ColorDbl operator+=(const ColorDbl& c) {
	//	return ColorDbl(color.r + c.color.r, color.g + c.color.g, color.b + c.color.b);
	//}
private:
	glm::vec3 color{0,0,0}; //background is black.
};