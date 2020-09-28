#pragma once
#include "Ray.h"
#include "ColorDbl.h"
#include "Material.h"
class Object
{
public:
	Object() {};

	virtual ~Object() = 0 {};
	virtual bool castRay(Ray& ray, float& t, float& t_closest, ColorDbl& col) = 0;
	//material properties:
	Material getMaterial() const
	{
		return material;
	}

	Material material;
};