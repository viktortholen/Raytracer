#pragma once
#include "Includer.h"
#include "Object.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Object {
public:
	Sphere(const float& _r, const Vec4& _center, const Material &m)
		:r{ _r }, center{ _center }, material{m}{}
	~Sphere() = default;

	virtual bool castRay(Ray& ray, float& t, float& t_closest, ColorDbl& col) override
	{

		Vec4 o = ray.ps;
		Vec4 I = (ray.pe - ray.ps).normalize(); //direction
		float a = I.dotProduct(I);
		float b = 2.0f * I.dotProduct(o - center);
		float c = (o - center).dotProduct(o - center) - pow(r,2);
		float discriminant = b * b - 4 * a * c;
		float d1 = (-b / 2) - sqrt(pow(b / 2, 2) - (a * c));
		float d2 = (-b / 2) + sqrt(pow(b / 2, 2) - (a * c));

		if (discriminant < 0) return false;

		if (d1 < 0)
		{
			std::cout << "here";
			d1 = d2;
		}
		if (d1 < 0)
		{
			std::cout << "here";
			return false;
		}
		if (d1 < t_closest)
		{
			t_closest = d1;
			col = material.diff_col;
		}
		//std::cout << "d1: " << d1 << ", d2: " << d2 << std::endl;
		
		
		return true;
	}

private:
	float r; //radius
	Vec4 center; //center

	Material material;
};