#pragma once
#include "Includer.h"
#include "Object.h"
#include "Triangle.h"
#include "Material.h"
class Mesh : public Object{
public:
	Mesh(const Material &m): material{m}{}
	~Mesh();
	Mesh& operator=(const Mesh& m)
	{
		Mesh tmp{ m };
		std::swap(tmp.triangleList, triangleList);
		std::swap(tmp.material, material);

	}
	Mesh(const Mesh& m)
	{
		triangleList = m.triangleList;
		material = m.material;
	}
	void addTriangleToMesh(Triangle *t);
	std::vector<std::shared_ptr<Triangle>> getTriangleList() const;
	virtual bool castRay(Ray& ray, float& t_closest) const override;
	Material getMaterial() const override;

private:
	std::vector<std::shared_ptr<Triangle>> triangleList;
	Material material;
};