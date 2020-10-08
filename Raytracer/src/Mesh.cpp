#pragma once
#include "Mesh.h"

Mesh:: ~Mesh()
{
	for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); ++it) {
		delete* it;
	}
	triangleList.clear();
}
std::list<Triangle*> Mesh::getTriangleList() const
{
	return triangleList;
}
bool Mesh::castRay(Ray& ray, float& t_closest)
{
	float t;
	bool hit = false;
	for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
	{
		if ((*it)->rayIntersection(ray, t) && t < t_closest)
		{
			hit = true;
			ray.setTriangle(*it);
			ray.setEndPoint(t);
			ray.setHitNormal((*it)->getNormal().normalize());
			t_closest = t;
			//ray.endPointTriangle = (*it);
			//ray.pe = ray.ps + (t * ray.dir.normalize()); //set the endpoint
			//ray.hitNormal =(*it)->getNormal().normalize();
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