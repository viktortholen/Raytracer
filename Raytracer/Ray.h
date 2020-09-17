#pragma once
#include "Includer.h"
#include "Triangle.h"
#include "ColorDbl.h"
#include "Vertex.h"

class Ray {
public:
	Ray(const Vertex& start, const Vertex& end)
		:ps{start}, pe{end}
	{
		vertex_list.push_back(start);
		vertex_list.push_back(end);
		//endPointTriangle = new Triangle();
	}
	~Ray() {
		delete endPointTriangle;
	}
	Ray(const Ray& other)
		:ps{ other.ps }, pe{pe}{ //copy

		vertex_list = other.vertex_list;
		color = other.color;
	}
	Ray& operator=(Ray& p) { //assignment
		Ray temp{ p };
		std::swap(p.ps, ps);
		std::swap(p.pe, pe);
		std::swap(p.color, color);
		std::swap(p.vertex_list, vertex_list);
		std::swap(p.endPointTriangle, endPointTriangle);

		return *this;
	}

private:
	Vertex ps, pe;
	
	std::list<Vertex> vertex_list;
	ColorDbl color{0,0,0};
	Triangle* endPointTriangle;

	friend class Triangle;
};