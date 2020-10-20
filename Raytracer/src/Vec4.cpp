#pragma once

#include "Vec4.h"
Vec4::Vec4(const Vec4& other) {
	coords = other.coords;
}
Vec4& Vec4::operator=(const Vec4 &p) { //assignment
	Vec4 tmp{ p };
	std::swap(tmp.coords, coords);
	return *this;
}

Vec4 Vec4::operator-(const Vec4& v) const {
	Vec4 tmp{ *this };
	tmp.coords[0] -= v.coords[0];
	tmp.coords[1] -= v.coords[1];
	tmp.coords[2] -= v.coords[2];
	return tmp;
}
Vec4 Vec4::operator-(const float& v) const {
	Vec4 tmp{ *this };
	tmp.coords[0] -= v;
	tmp.coords[1] -= v;
	tmp.coords[2] -= v;
	return tmp;
}
Vec4 Vec4::operator+(const Vec4& v) const {
	Vec4 tmp{ *this };
	tmp.coords[0] += v.coords[0];
	tmp.coords[1] += v.coords[1];
	tmp.coords[2] += v.coords[2];
	return tmp;
}
Vec4 Vec4::operator*(const float& f)
{
	coords[0] *= f;
	coords[1] *= f;
	coords[2] *= f;
	return *this;
}

Vec4 Vec4::crossProduct(const Vec4& v) const
{
	glm::vec3 res = glm::cross(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
	return Vec4(res[0], res[1], res[2], 1);
}
float Vec4::dotProduct(const Vec4& v) const
{
	return glm::dot(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
}
float Vec4::euclideanDist() const
{
	return sqrtf(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
}
void Vec4::printCoords()
{
	std::cout << "\nx: " << coords[0] << ", y: " << coords[1] << " , z: " << coords[2];
}

Vec4 Vec4::normalize()
{
	glm::vec3 tmp = { coords[0],coords[1] ,coords[2] };
	tmp = glm::normalize(tmp);
	return Vec4{ tmp[0], tmp[1] ,tmp[2], coords[3] };
}
Vec4 Vec4::reflect(const Vec4& N) //direction and normal
{
	Vec4 dir{ *this };
	return dir - 2 * dir.dotProduct(N) * N;
}