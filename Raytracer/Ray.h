#pragma once
#include "Includer.h"
#include "ColorDbl.h"
#include "Vertex.h"
#include "Triangle.h"
class Ray {
public:
	Ray(const Vertex& start, const Vertex& end)
	{
		vertex_list.push_back(start);
		vertex_list.push_back(end);

		/*startPoint = vertex_list.front();
		endPoint = vertex_list.back();*/
	}
private:
	//Vertex& startPoint, endPoint;
	
	std::list<Vertex> vertex_list;
	ColorDbl color;
	//Triangle* endPointTriangle = new Triangle();
};