#pragma once

#include "Includer.h"
#include "Ray.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Ray; //forward declaration

class Triangle {
public:
	Triangle() = default;
	Triangle(const Vertex& _v0, const Vertex& _v1, const Vertex& _v2, const ColorDbl& _color)
		:v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, color{_color}
	{
		calculateNormal();
	}
	bool rayIntersection(Ray ray);

	~Triangle() = default;

	Triangle(const Triangle& other);

	Triangle& operator=(Triangle &p);


	void calculateNormal();

private:
	ColorDbl color{255,255,255};
	Direction normal{ 0,0,0 };
	Vertex v0, v1, v2;
};