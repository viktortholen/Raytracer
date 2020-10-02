#pragma once
#include "ColorDbl.h"
#include "Vec4.h"
class Light {
public:
	Light(const Vec4& pos, const float& size)
		:position{pos},d {size}, emit_color{ 0,0,0 } {}

	Vec4 getPosition() const
	{
		return position;
	}
	float getIntensity() const
	{
		return intensity;
	}
private:

	//int samples;
	ColorDbl emit_color{ 255,255,255 };
	float intensity = 1.0f;
	float d; //size
	Vec4 position;
};