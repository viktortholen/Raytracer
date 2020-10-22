#pragma once
#include "Includer.h"
#include "Object.h"
#include "Triangle.h"
#include "Material.h"
class Mesh : public Object{
public:
	Mesh(const Material &m): material{m}{}
	~Mesh();

	void addTriangleToMesh(Triangle *t);
	std::vector<Triangle*> getTriangleList() const;
	virtual bool castRay(Ray& ray, float& t_closest) const override;
	Material getMaterial() const override;

private:
	std::vector<Triangle*> triangleList;
	Material material;
};