#pragma once
#include "Includer.h"
#include "Object.h"
#include "Triangle.h"

class Mesh : public Object{
public:
	Mesh(){}
	~Mesh()
	{
		for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); ++it) {
			delete* it;
		}
		triangleList.clear();
	}

	void addTriangleToMesh(Triangle *t);
	std::list<Triangle*> getTriangleList() const
	{
		return triangleList;
	}
	virtual bool castRay(Ray &ray, float &t, float &t_closest, ColorDbl &col) override
	{
		bool hit = false;
		for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
		{
			if ((*it)->rayIntersection(ray, t) && t < t_closest)
			{
				hit = true;
				ray.setTriangle(**it);
				t_closest = t;

				col = (*it)->getColor();
			}
			
		}
		return hit;
	}

private:
	std::list<Triangle*> triangleList;
	Material material;
};

void Mesh::addTriangleToMesh(Triangle *t)
{
	triangleList.push_back(t);
}