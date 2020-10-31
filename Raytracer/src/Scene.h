#pragma once
#include "Includer.h"
#include "Object.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Material.h"
#include "Vec4.h"
#include "Light.h"

class Scene {
public:
	Scene() = default;
	~Scene();
	Scene& operator=(const Scene& s)
	{
		Scene tmp{ s };
		std::swap(tmp.lightList, lightList);
		std::swap(tmp.objectList, objectList);

	}
	Scene(const Scene& s)
	{
		lightList = s.lightList;
		objectList = s.objectList;
	}
	void createScene();
	void createRoom(const Material& m);

	void createTetra(const Vec4& p, const float& size, const Material& m);
	void createSphere(const Vec4& p, const float& size, const Material& m);
	void createCube(const Vec4& p, const float& height, const float& width, const Material& m);
	void createPlane(const Vec4& p, const float& size, const Material& m);
	std::vector<std::shared_ptr<Object>> getObjectList() const;
	std::vector<std::shared_ptr<Mesh>> getLightList() const;
private:
	std::vector<std::shared_ptr<Object>> objectList;
	std::vector<std::shared_ptr<Mesh>> lightList;

};