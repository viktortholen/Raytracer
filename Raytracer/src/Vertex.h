#pragma once
#include "Includer.h"
#include "Triangle.h"
class Vertex {
public:
	Vertex() = default;
	Vertex(float x, float y, float z, float w = 0)
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

	Vertex operator-(const Vertex& v) {
		Vertex tmp{ *this };
		tmp.coords =- v.coords;
		return tmp;
	}
	//glm::vec4 getCoords() {
	//	return coords;
	//}

	Vertex operator*(const Vertex& v) {
		Vertex tmp{ *this };
		glm::vec3 vec1 = glm::vec3(coords[0], coords[1], coords[2]);
		glm::vec3 vec2 = glm::vec3(v.coords[0], v.coords[1], v.coords[2]);
		glm::vec3 res = glm::cross(vec1, vec2);
		return Vertex(res[0], res[1], res[2], 1); //w = 0 eller 1?

	}

private:
	glm::vec4 coords;
	friend class Triangle;
};
