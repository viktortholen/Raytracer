#pragma once
#include "Mesh.h"

Mesh:: ~Mesh()
{
	for (std::vector<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); ++it) {
		delete* it;
	}
	triangleList.clear();
}
std::vector<Triangle*> Mesh::getTriangleList() const
{
	return triangleList;
}
bool Mesh::castRay(Ray& ray, float& t_closest) const
{
	float t;
	bool hit = false;
	for (std::vector<Triangle*>::const_iterator it = triangleList.cbegin(); it != triangleList.cend(); it++)
	{
		if ((*it)->rayIntersection(ray, t) && t < t_closest)
		{
			hit = true;
			ray.setHitPropertiesMesh(*it, t);
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
	triangleList.push_back(t);
}