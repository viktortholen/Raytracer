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
	Triangle* getTriangle();
	Vec4 getDirection()
	{
		return dir;
	}
	Vec4 getHitNormal()
	{
		return hitNormal;
	}
private:
	friend class Triangle;
	friend class Sphere;
	friend class Camera;
	friend class Mesh;
	Vec4 ps, pe;
	//std::list<Vec4> vertex_list;
	ColorDbl color{0,0,0};
	Triangle* endPointTriangle = NULL;
	Vec4 dir;
	Vec4 hitNormal;
};