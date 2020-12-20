#pragma once
#include "Mesh.h"

Mesh:: ~Mesh()
{
	triangleList.clear();
}
std::vector<std::shared_ptr<Triangle>> Mesh::getTriangleList() const
{
	return triangleList;
}
bool Mesh::castRay(Ray& ray, float& t_closest) const
{
	float t;
	bool hit = false;
	for (const auto triangle: triangleList)
	{
		if (triangle->rayIntersection(ray, t) && t < t_closest)
		{
			hit = true;
			ray.setHitPropertiesMesh(triangle.get(), t);
			t_closest = t;
		}

	}
	return hit;
}

Material Mesh::getMaterial() const
{
	return material;
}
void Mesh::addTriangleToMesh(Triangle* t)
{
	triangleList.push_back(std::shared_ptr<Triangle>(t));
}