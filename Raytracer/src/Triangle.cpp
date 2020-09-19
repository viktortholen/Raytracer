
#include "Triangle.h"


	Vertex Triangle::rayIntersection(Ray ray) {
		Vertex T = ray.ps - v0;
		Vertex E1 = v1 - v0;
		Vertex E2 = v2 - v0;
		Vertex D = ray.pe - ray.ps;
		Vertex P = D * E2;
		Vertex Q = T * E1;

		return Q;
	}
	Triangle::Triangle(const Triangle& other)
	{
		v0 = other.v0;
		v1 = other.v1;
		v2 = other.v2;
		normal = other.normal;
		color = other.color;
	}

	Triangle& Triangle::operator=(Triangle p) { //assignment
		std::swap(p.color, color);
		std::swap(p.v0, v0);
		std::swap(p.v1, v1);
		std::swap(p.v2, v2);
		std::swap(p.normal, normal);
		return *this;
	}

	void Triangle::calculateNormal()
	{
		Vertex U = v1 - v0;
		Vertex V = v2 - v0;

		glm::vec4 Uc = U.coords;
		glm::vec4 Vc = V.coords;


		float Nx = (Uc.y * Vc.z) - (Uc.z * Vc.y);
		float Ny = (Uc.z * Vc.x) - (Uc.x * Vc.z);
		float Nz = (Uc.x * Vc.y) - (Uc.y * Vc.x);

		//double Nx = (U.y * V.z) - (U.z * V.y);
		//double Ny = (U.z * V.x) - (U.x * V.z);
		//double Nz = (U.x * V.y) - (U.y * V.x);
		normal = Direction{ Nx,Ny,Nz };
	}