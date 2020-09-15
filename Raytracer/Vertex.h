#pragma once
#include "Includer.h"

class Vertex {
public:
	Vertex() = default;
	Vertex(float _x, float _y, float _z, float _w = 0)
		:x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
private:
	float x, y, z, w;
};
