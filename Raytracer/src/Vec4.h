#pragma once
#include "Includer.h"
//#include "Triangle.h"

class Vec4 {
public:
	Vec4() = default;
	Vec4(float x, float y, float z, float w = 1)
		:coords{x, y, z, w } {}
	~Vec4() = default;

	Vec4(const Vec4& other);
	Vec4& operator=(const Vec4 &p);

	Vec4 operator-(const Vec4& v) const;
	Vec4 operator-(const float& v) const;
	Vec4 operator+(const Vec4& v) const;
	Vec4 operator*(const float& f) const;
	friend Vec4 operator* (const float& r, const Vec4& v)
	{
		return Vec4(v.coords[0] * r, v.coords[1] * r, v.coords[2] * r, v.coords[3]);
	}

	Vec4 crossProduct(const Vec4& v) const;
	float dotProduct(const Vec4& v) const;
	float euclideanDist() const;
	void printCoords();
	
	Vec4 normalize();
	Vec4 reflect(const Vec4& N);
	Vec4 refract(const Vec4& N, const float& n1, const float& n2);

	glm::vec4 coords;


};