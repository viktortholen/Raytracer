#pragma once

#include "Includer.h"
#include "Ray.h"
#include "Vec4.h"
#include "ColorDbl.h"
#include "Direction.h"

class Ray; //forward declaration

class Triangle {
public:
	Triangle() {
		calculateNormal();
	}
	Triangle(const Vec4& _v0, const Vec4& _v1, const Vec4& _v2, const ColorDbl& _color)
		:v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, color{_color}
	{
		calculateNormal();
	}
	bool rayIntersection(Ray& ray, float& t) const;

	~Triangle() = default;

	Triangle(const Triangle& other);

	Triangle& operator=(const Triangle &p);

	void calculateNormal();
	float calculateArea() const;
	Vec4 pickRandomPoint(const float& u, const float& v) const;
	Vec4 getNormal() const
	{
		return normal;
	}
	ColorDbl getColor() const;

private:
	ColorDbl color{255,255,255};
	Vec4 normal{ 0,0,0 };
	Vec4 v0, v1, v2;
};