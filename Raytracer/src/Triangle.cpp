
#include "Triangle.h"


bool Triangle::rayIntersection(Ray& ray, float& t) const {
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
Triangle::Triangle(const Triangle& other)
{
	v0 = other.v0;
	v1 = other.v1;
	v2 = other.v2;
	normal = other.normal;
	color = other.color;
}

Triangle& Triangle::operator=(const Triangle& p) { //assignment
	Triangle tmp{ p };
	std::swap(tmp.color, color);
	std::swap(tmp.v0, v0);
	std::swap(tmp.v1, v1);
	std::swap(tmp.v2, v2);
	std::swap(tmp.normal, normal);
	return *this;
}

void Triangle::calculateNormal()
{
	Vec4 U = v1 - v0;
	Vec4 V = v2 - v0;

	normal = U.crossProduct(V);
}

float Triangle::calculateArea() const
{
	float a = (v1 - v0).euclideanDist();
	float b = (v2 - v0).euclideanDist();
	float c = (v2 - v1).euclideanDist();
	float s = (a + b + c) / 2;

	return sqrtf(s * (s - a) * (s - b) * (s - c));

	//Vec4 A = 0.5*((v1 - v0).crossProduct(v2-v0));
	//A.printCoords();
	//return A.euclideanDist();
}
Vec4 Triangle::pickRandomPoint(const float &u, const float &v) const
{
	return (1 - u - v) * v0 + u * v1 + v * v2;
	//return u * (v1 - v0) + v * (v2 - v0);
}
ColorDbl Triangle::getColor() const {
	return color;
}