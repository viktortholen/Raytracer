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

	virtual bool castRay(Ray& ray, float& t_closest) const override
	{
		Vec4 o = ray.getStartPoint();
		Vec4 I = ray.getDirection(); //direction
		float a = I.dotProduct(I);
		float b = 2.0f * I.dotProduct(o - center);
		float c = (o - center).dotProduct(o - center) - pow(r,2);
		float discriminant = b * b - (4 * a * c);
		float d1 = (-b / 2) - sqrt(pow(b / 2, 2) - (a * c));
		float d2 = (-b / 2) + sqrt(pow(b / 2, 2) - (a * c));

		if (discriminant < 0) return false;

		if (d1 < 0)
		{
			d1 = d2;
		}
		if (d1 < 0)
		{
			return false;
		}
		if (d1 > t_closest)
		{
			return false;
		}


		t_closest = d1;

		ray.setHitPropertiesSphere(center ,material.diff_col, d1);

		return true;
	}
	Material getMaterial() const override
	{
		return material;
	}
private:
	float r; //radius
	Vec4 center; //center
	Material material;
};