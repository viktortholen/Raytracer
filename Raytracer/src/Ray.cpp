#include "Ray.h"


Ray::Ray(const Vec4& start, const Vec4& _dir) 
	: ps{ start }, dir{_dir}
{
}
Ray::~Ray()
{
}
Ray::Ray(const Ray& other)
:ps{ other.ps }, pe{ pe }
{ //copy
	color = other.color;
}
Ray& Ray::operator=(Ray &p) 
{
	Ray temp{ p };
	std::swap(p.ps, ps);
	std::swap(p.pe, pe);
	std::swap(p.color, color);
	std::swap(p.endPointTriangle, endPointTriangle);

	return *this;
}
void Ray::setTriangle(Triangle* t)
{
	endPointTriangle = t;
}
Triangle* Ray::getTriangle(){
	return endPointTriangle;
}