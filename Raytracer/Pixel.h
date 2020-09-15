#pragma once
#include "Includer.h"
#include "Ray.h"
#include "ColorDbl.h"
class Pixel {
public:
	Pixel() = default;
	Pixel(const ColorDbl& _color, Ray _ray)
		:color{_color}, ray{_ray}{}
private:
	ColorDbl color;
	Ray& ray;

};