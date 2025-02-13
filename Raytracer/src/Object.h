#pragma once
#include "Ray.h"
#include "ColorDbl.h"
#include "Material.h"

class Object
{
public:
	Object() {};

	virtual ~Object() = 0 {};
	virtual bool castRay(Ray& ray, float& t_closest) const = 0;
	//material properties:
	virtual Material getMaterial() const = 0;

};