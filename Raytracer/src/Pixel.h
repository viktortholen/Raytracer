#pragma once
#include "Includer.h"
#include "Ray.h"
#include "ColorDbl.h"

class Pixel {
public:
	Pixel() = default;
	Pixel(const ColorDbl& _color, Ray _ray)
		:color{_color}, ray{&_ray}{}

	~Pixel() {

	}
	Pixel(const Pixel& other) { //copy
		color = other.color;
		ray = other.ray;
	}
	Pixel& operator=(const Pixel& p) { //assignment
		Pixel tmp{ p };
		std::swap(tmp.color, color);
		std::swap(tmp.ray, ray);
		return *this;
	}

	void setColor(const ColorDbl& rgb)
	{
		color = rgb;
	}
	glm::vec3 getColorVec() const
	{
		return color.getColorVec();
	}
	ColorDbl getColor() const
	{
		return color;
	}

private:
	ColorDbl color{0,0,0};
	Ray* ray = NULL;

};