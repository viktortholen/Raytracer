
#include "Triangle.h"


bool Triangle::rayIntersection(Ray& ray, float& t) {
	const float EPSILON = 0.00001f;


	Vec4 T = ray.getStartPoint() - v0;
	Vec4 E1 = v1 - v0;
	Vec4 E2 = v2 - v0;
	//Vec4 D = ray.pe - ray.ps;
	Vec4 D = ray.getDirection();
	Vec4 P = D.crossProduct(E2);
	Vec4 Q = T.crossProduct(E1);
	

	float u = P.dotProduct(T) / P.dotProduct(E1);

	if (u < EPSILON)
		return false;

	float v = Q.dotProduct(D) / P.dotProduct(E1);

	if (v < EPSILON)
		return false;

	if (static_cast<float>(u + v) > 1)
		return false;

	t = Q.dotProduct(E2) / P.dotProduct(E1);
	//std::cout << "\n "<<t << " " << u << " " << v;
	if (t < EPSILON)
	{
		return false;
	}
	return true;
}
//Triangle::Triangle(const Triangle& other)
//{
//	v0 = other.v0;
//	v1 = other.v1;
//	v2 = other.v2;
//	normal = other.normal;
//	color = other.color;
//}

//Triangle& Triangle::operator=(const Triangle& p) { //assignment
//	Triangle tmp{ *this };
//	std::swap(tmp.color, color);
//	std::swap(tmp.v0, v0);
//	std::swap(tmp.v1, v1);
//	std::swap(tmp.v2, v2);
//	std::swap(tmp.normal, normal);
//	return *this;
//}

void Triangle::calculateNormal()
{
	Vec4 U = v1 - v0;
	Vec4 V = v2 - v0;

	glm::vec4 Uc = U.coords;
	glm::vec4 Vc = V.coords;


	float Nx = (Uc.y * Vc.z) - (Uc.z * Vc.y);
	float Ny = (Uc.z * Vc.x) - (Uc.x * Vc.z);
	float Nz = (Uc.x * Vc.y) - (Uc.y * Vc.x);

	//double Nx = (U.y * V.z) - (U.z * V.y);
	//double Ny = (U.z * V.x) - (U.x * V.z);
	//double Nz = (U.x * V.y) - (U.y * V.x);
	normal = Vec4{ Nx,Ny,Nz };
}
ColorDbl Triangle::getColor() {
	return color;
}