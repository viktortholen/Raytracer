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
	void createScene();
	void createRoom(const Material& m);

	void createTetra(const Vec4& p, const float& size, const Material& m);
	void createSphere(const Vec4& p, const float& size, const Material& m);
	void createCube(const Vec4& p, const float& size, const Material& m);
	void createPlane(const Vec4& p, const float& size, const Material& m);
	std::list<Object*> getObjectList() const;
	std::list<Mesh*> getLightList() const;
private:
	std::list<Object*> objectList;
	std::list<Mesh*> lightList;

};