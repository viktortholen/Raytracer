#pragma once
#include "Includer.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Triangle {
public:
	Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
		:a{v1}, b{v2}, c{v3}{}
	//Vertex rayIntersection(Ray arg) {
	//	Vertex* intersection = new Vertex(0,0,0,0);
	//	return *intersection;
	//}
private:
	ColorDbl color;
	Direction normal;
	Vertex a, b, c;

};