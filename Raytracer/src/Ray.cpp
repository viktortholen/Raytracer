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
	hitColor = other.hitColor;
}
Ray& Ray::operator=(const Ray &p) 
{
	Ray tmp{ p };
	std::swap(tmp.ps, ps);
	std::swap(tmp.pe, pe);
	std::swap(tmp.hitColor, hitColor);
	std::swap(tmp.endPointTriangle, endPointTriangle);

	return *this;
}
//void Ray::setTriangle(Triangle* t)
//{
//	endPointTriangle = t;
//}
//void Ray::setHitNormal(const Vec4& n)
//{
//	hitNormal = n;
//}
//void Ray::setEndPoint(const float &t)
//{
//	pe = ps + (t * dir.normalize());
//}
void Ray::setHitPropertiesMesh(Triangle* t, const float& d)
{
	endPointTriangle = t;
	hitNormal = t->getNormal().normalize();
	pe = ps + (d * dir.normalize());
	hitColor = t->getColor();
}
void Ray::setHitPropertiesSphere(const Vec4& center, const ColorDbl& c, const float& d)
{
	pe = ps + (d * dir.normalize());
	hitNormal = (pe - center).normalize();
	hitColor = c;
}
Triangle* Ray::getTriangle(){
	return endPointTriangle;
}
Vec4 Ray::getOffsetEndPointAlongNormal(const float& amount)
{
	return pe + (amount * hitNormal);
}
