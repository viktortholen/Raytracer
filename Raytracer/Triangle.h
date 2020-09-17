#pragma once
#include "Includer.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Triangle {
public:
	Triangle() = default;
	Triangle(const Vertex& _v1, const Vertex& _v2, const Vertex& _v3, const ColorDbl& _color)
		:v1{ _v1 }, v2{ _v2 }, v3{ _v3 }, color{_color}
	{
		calculateNormal();
	}
	//Vertex rayIntersection(Ray arg) {
	//	Vertex* intersection = new Vertex(0,0,0,0);
	//	return *intersection;
	//}
	~Triangle() = default;

	Triangle(const Triangle& other)
	{
		v1 = other.v1;
		v2 = other.v2;
		v3 = other.v3;
		normal = other.normal;
		color = other.color;
	}

	Triangle& operator=(Triangle p) { //assignment
		std::swap(p.color, color);
		std::swap(p.v1, v1);
		std::swap(p.v2, v2);
		std::swap(p.v3, v3);
		std::swap(p.normal, normal);
		return *this;
	}
	void calculateNormal()
	{
		Vertex U = v2 - v1;
		Vertex V = v3 - v1;

		float Nx = (U.y * V.z) - (U.z * V.y);
		float Ny = (U.z * V.x) - (U.x * V.z);
		float Nz = (U.x * V.y) - (U.y * V.x);

		normal = Direction{Nx,Ny,Nz};
	}
private:
	ColorDbl color{255,255,255};
	Direction normal{ 0,0,0 };
	Vertex v1, v2, v3;

};