#pragma once
#include "Includer.h"
#include "Object.h"
#include "Triangle.h"
#include "Material.h"
class Mesh : public Object{
public:
	Mesh(const Material &m): material{m}{}
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
	virtual bool castRay(Ray &ray, float &t, float &t_closest) override
	{
		bool hit = false;
		for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
		{
			if ((*it)->rayIntersection(ray, t) && t < t_closest)
			{
				hit = true;
				
				t_closest = t;

				//col = (*it)->getColor();
			}
			
		}
		return hit;
	}
	Material getMaterial() const override
	{
		return material;
	}

private:
	std::list<Triangle*> triangleList;
	Material material;
};

void Mesh::addTriangleToMesh(Triangle *t)
{
	triangleList.push_back(t);
}