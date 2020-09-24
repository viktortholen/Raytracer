#pragma once
#include "Includer.h"
#include "Triangle.h"
class Mesh {
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
private:
	std::list<Triangle*> triangleList;
};

void Mesh::addTriangleToMesh(Triangle *t)
{
	triangleList.push_back(t);
}