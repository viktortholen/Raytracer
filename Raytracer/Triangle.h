#pragma once
#include "Includer.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Triangle {
public:
	Triangle(const Vertex& _v1, const Vertex& _v2, const Vertex& _v3, const ColorDbl& _color)
		:v1{ _v1 }, v2{ _v2 }, v3{ _v3 }, color{_color}{}
	//Vertex rayIntersection(Ray arg) {
	//	Vertex* intersection = new Vertex(0,0,0,0);
	//	return *intersection;
	//}
	~Triangle() = default;

	Triangle(const Triangle& other) { //copy
		v1 = other.v1;
		v2 = other.v2;
		v3 = other.v3;
	}
	Triangle& operator=(Triangle& p) { //assignment
		Triangle temp{ p };
		std::swap(p.color, color);
		std::swap(p.v1, v1);
		std::swap(p.v2, v2);
		std::swap(p.v3, v3);
		return *this;
	}

private:
	ColorDbl color{255,255,255};
	//Direction normal;
	Vertex v1, v2, v3;

};