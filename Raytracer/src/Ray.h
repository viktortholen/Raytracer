#pragma once
#include "Includer.h"
#include "Vertex.h"
#include "ColorDbl.h"

#include "Triangle.h"
class Triangle; //forward declaration

class Ray {
public:
	Ray(const Vertex& start, const Vertex& end);

	~Ray();

	Ray(const Ray& other);
	Ray& operator=(Ray &p);
	void setTriangle(Triangle t);
private:
	friend class Triangle;

	Vertex ps, pe;
	std::list<Vertex> vertex_list;
	ColorDbl color{0,0,0};
	Triangle* endPointTriangle = NULL;
};