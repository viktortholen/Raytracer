#pragma once
#include "Includer.h"
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include "Ray.h"
class Triangle {
public:
	Triangle() = default;
	Triangle(const Vertex& _v0, const Vertex& _v1, const Vertex& _v2, const ColorDbl& _color)
		:v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, color{_color}
	{
		calculateNormal();
	}
	Vertex rayIntersection(Ray ray) {
		Vertex T = ray.ps - v0;
		Vertex E1 = v1 - v0;
		Vertex E2 = v2 - v0;
		Vertex D = ray.pe - ray.ps;
		Vertex P = D * E2;
		Vertex Q = T * E1;
	}
	~Triangle() = default;

	Triangle(const Triangle& other)
	{
		v0 = other.v0;
		v1 = other.v1;
		v2 = other.v2;
		normal = other.normal;
		color = other.color;
	}

	Triangle& operator=(Triangle p) { //assignment
		std::swap(p.color, color);
		std::swap(p.v0, v0);
		std::swap(p.v1, v1);
		std::swap(p.v2, v2);
		std::swap(p.normal, normal);
		return *this;
	}
	void calculateNormal()
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
		normal = Direction{Nx,Ny,Nz};
	}
private:
	ColorDbl color{255,255,255};
	Direction normal{ 0,0,0 };
	Vertex v0, v1, v2;
};