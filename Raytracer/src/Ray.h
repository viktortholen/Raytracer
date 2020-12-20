#pragma once
#include "Includer.h"
#include "Vec4.h"
#include "ColorDbl.h"

#include "Triangle.h"
class Triangle; //forward declaration

class Ray {
public:
	Ray(const Vec4& start, const Vec4& _dir);
	~Ray();

	Ray(const Ray& other);
	Ray& operator=(const Ray &p);
	void setHitPropertiesMesh(Triangle* t, const float& d);
	void setHitPropertiesSphere(const Vec4& n, const ColorDbl& c, const float& d);
	Vec4 getOffsetEndPointAlongNormal(const float& amount);
	Triangle* getTriangle();
	Vec4 getDirection()
	{
		return dir;
	}
	Vec4 getHitNormal()
	{
		return hitNormal;
	}
	Vec4 getStartPoint()
	{
		return ps;
	}
	Vec4 getEndPoint()
	{
		return pe;
	}
	ColorDbl getColor()
	{
		return hitColor;
	}
private:

	Vec4 ps, pe;
	ColorDbl hitColor{0,0,0};
	Triangle* endPointTriangle = NULL;
	Vec4 dir;
	Vec4 hitNormal;
};