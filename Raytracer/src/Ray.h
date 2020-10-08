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
	Ray& operator=(Ray &p);
	void setTriangle(Triangle* t);
	void setHitNormal(const Vec4& n);
	void setEndPoint(const float& t);
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
protected:

	Vec4 ps, pe;
	ColorDbl color{0,0,0};
	Triangle* endPointTriangle = NULL;
	Vec4 dir;
	Vec4 hitNormal;
};