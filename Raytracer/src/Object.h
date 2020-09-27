#pragma once
#include "Mesh.h"

class Object
{
public:
	Object() {};

	virtual ~Object() = 0 {};
	virtual bool castRay(Ray& ray, float& t, float& t_closest, ColorDbl& col) = 0;

	//material properties:
	struct Material {
		enum Type
		{
			DIFFUSE, REFLECTIVE
		};
		//Lambertian properties i dont know...
		int Kd;//?
	};
};