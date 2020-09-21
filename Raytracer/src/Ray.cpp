#include "Ray.h"


Ray::Ray(const Vertex& start, const Vertex& end) : ps{start}, pe{end}
{
	//vertex_list.push_back(start); //crashes dr memory
	//vertex_list.push_back(end);
}
Ray::~Ray() 
{
	vertex_list.clear();
	delete endPointTriangle;
}
Ray::Ray(const Ray& other)
:ps{ other.ps }, pe{ pe }
{ //copy

	vertex_list = other.vertex_list;
	color = other.color;
}
Ray& Ray::operator=(Ray &p) 
{
	Ray temp{ p };
	std::swap(p.ps, ps);
	std::swap(p.pe, pe);
	std::swap(p.color, color);
	std::swap(p.vertex_list, vertex_list);
	std::swap(p.endPointTriangle, endPointTriangle);

	return *this;
}
void Ray::setTriangle(Triangle t)
{
	endPointTriangle = &t;
}
