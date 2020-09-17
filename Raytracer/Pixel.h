#pragma once
#include "Includer.h"
#include "Ray.h"
#include "ColorDbl.h"

class Pixel {
public:
	Pixel() {}
	Pixel(const ColorDbl& _color, Ray _ray)
		:color{_color}, ray{&_ray}{}

	~Pixel() {
		delete ray;
	}
	Pixel(const Pixel& other) { //copy
		color = other.color;
		ray = other.ray;
	}
	Pixel& operator=(Pixel& p) { //assignment
		Pixel temp{ p };
		std::swap(p.color, color);
		std::swap(p.ray, ray);
		return *this;
	}

private:
	ColorDbl color;
	Ray* ray;

};