#pragma once
#include "Includer.h"
#include "Triangle.h"
class Vertex {
public:
	Vertex() = default;
	Vertex(float _x, float _y, float _z, float _w = 0)
		:x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
	~Vertex() = default;

	Vertex(const Vertex& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	Vertex& operator=(Vertex p) { //assignment
		Vertex temp{ p };
		std::swap(p.x, x);
		std::swap(p.y, y);
		std::swap(p.z, z);
		std::swap(p.w, w);
		return *this;
	}

	Vertex operator-(const Vertex& v) {
		Vertex tmp{ *this };
		tmp.x -= v.x;
		tmp.y -= v.y;
		tmp.z -= v.z;
		tmp.w -= v.w;
		return tmp;
	}

private:
	float x, y, z, w;
	friend class Triangle;
};
