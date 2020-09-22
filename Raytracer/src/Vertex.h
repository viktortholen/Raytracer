#pragma once

//#include "Triangle.h"
class Vertex {
public:
	Vertex() = default;
	Vertex(float x, float y, float z, float w = 1)
		:coords{x, y, z, w } {}
	~Vertex() = default;

	Vertex(const Vertex& other) {
		coords = other.coords;

	}

	Vertex& operator=(Vertex p) { //assignment
		Vertex temp{ p };
		std::swap(p.coords, coords);
		return *this;
	}

	Vertex operator-(const Vertex& v) const{
		Vertex tmp{ *this };
		tmp.coords[0] -= v.coords[0];
		tmp.coords[1] -= v.coords[1];
		tmp.coords[2] -= v.coords[2];
		return tmp;
	}
	Vertex crossProduct(const Vertex& v) const
	{
		glm::vec3 res = glm::cross(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
		return Vertex(res[0], res[1], res[2], 1);
	}
	float dotProduct(const Vertex& v) const
	{
		return glm::dot(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
	}
	void printCoords()
	{
		std::cout << "\nx: " << coords[0] << ", y: " << coords[1] << " , z: " << coords[2];
	}
private:
	glm::vec4 coords;
	friend class Triangle;
};
