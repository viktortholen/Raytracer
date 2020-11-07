#pragma once
#include "Scene.h"

Scene::~Scene()
{
	//std::cout << "\ndeleting scene";
	//for (auto it = objectList.begin(); it != objectList.end(); ++it) {
	//	delete& it;
	//}
	objectList.clear();
	//for (std::vector<Mesh*>::iterator it = lightList.begin(); it != lightList.end(); ++it) {
	//	if (*it != nullptr)
	//	{
	//		delete* it;
	//	}
	//	
	//}
	lightList.clear();
}
std::vector<std::shared_ptr<Object>> Scene::getObjectList() const {
	return objectList;
}
std::vector<std::shared_ptr<Mesh>> Scene::getLightList() const {
	return lightList;
}
void Scene::createScene() {
	Material diff_mat{ MaterialType::DIFFUSE_LAMBERTIAN, ColorDbl(255,255,255), 0.1f, 0.4f }; //room
	Material diff_mat2{ MaterialType::DIFFUSE_LAMBERTIAN, ColorDbl(255,255,255), 0.2f, 0.5f }; 
	Material diff_mat3{ MaterialType::DIFFUSE_LAMBERTIAN, ColorDbl(255,255,255), 0.99f , 0.9f};
	Material refl_mat{ MaterialType::REFLECTIVE_LAMBERTIAN, ColorDbl(255,255,255), 0.0f, 0.0f };
	Material emission_mat{ MaterialType::EMISSION, ColorDbl(255,255,255), 0.0f, 0.0f};

	//objects:
	//createTetra(Vec4(6, 0, -4), 2.0f, refl_mat);
	createCube(Vec4(8, 3, -1.5), 3.0f, 7.0f, diff_mat2);
	createCube(Vec4(6, -4, -4), 2.0f,2.0f, diff_mat3);
	createRoom(diff_mat);
	createSphere(Vec4(5, 3, -4), 1, refl_mat);
	//lights:
	createPlane(Vec4(7, -2, 4.9999), 2.0f, emission_mat);
	createPlane(Vec4(7, 2, 4.9999), 2.0f, emission_mat);
	

}
void Scene::createPlane(const Vec4& p, const float& size, const Material& m)
{
	Vec4 v0(p.coords[0] - size / 2, p.coords[1] - size / 2, p.coords[2]);
	Vec4 v1(p.coords[0] - size / 2, p.coords[1] + size / 2, p.coords[2]);
	Vec4 v2(p.coords[0] + size / 2, p.coords[1] + size / 2, p.coords[2]);
	Vec4 v3(p.coords[0] + size / 2, p.coords[1] - size / 2, p.coords[2]);

	Mesh* light = new Mesh(m);
	light->addTriangleToMesh(new Triangle(v0, v1, v3, m.diff_col));
	light->addTriangleToMesh(new Triangle(v1, v2, v3, m.diff_col));
	lightList.push_back(std::shared_ptr<Mesh>(light));

	Mesh* light_obj = new Mesh{m};
	light_obj->addTriangleToMesh(new Triangle(v0, v1, v3, m.diff_col));
	light_obj->addTriangleToMesh(new Triangle(v1, v2, v3, m.diff_col));
	objectList.push_back(std::shared_ptr<Mesh>(light_obj));

}
void Scene::createTetra(const Vec4& p, const float& size, const Material& m)
{
	Mesh* tetra = new Mesh(m);
	//Botten
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0] - size / 2, p.coords[1] + size / 2, p.coords[2] - size / 2), Vec4(p.coords[0] + size / 2, p.coords[1], p.coords[2] - size / 2), Vec4(p.coords[0] - size / 2, p.coords[1] - size / 2, p.coords[2] - size / 2), m.diff_col));
	//Mot kameran
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2] + size / 2), Vec4(p.coords[0] - size / 2, p.coords[1] + size / 2, p.coords[2] - size / 2), Vec4(p.coords[0] - size / 2, p.coords[1] - size / 2, p.coords[2] - size / 2), m.diff_col));
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2] + size / 2), Vec4(p.coords[0] - size / 2, p.coords[1] - size / 2, p.coords[2] - size / 2), Vec4(p.coords[0] + size / 2, p.coords[1], p.coords[2] - size / 2), m.diff_col));
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2] + size / 2), Vec4(p.coords[0] + size / 2, p.coords[1], p.coords[2] - size / 2), Vec4(p.coords[0] - size / 2, p.coords[1] + size / 2, p.coords[2] - size / 2), m.diff_col));
	objectList.push_back(std::shared_ptr<Object>(tetra));
}
void Scene::createSphere(const Vec4& p, const float& size, const Material& m)
{
	Sphere* sphere = new Sphere(size, p, m);
	objectList.push_back(std::shared_ptr<Sphere>(sphere));
}
void Scene::createCube(const Vec4& p, const float& width, const float& height, const Material& m)
{
	Mesh* cube = new Mesh(m);

	Vec4 v0(p.coords[0] - width / 2, p.coords[1] - width / 2, p.coords[2] - height / 2);
	Vec4 v1(p.coords[0] - width / 2, p.coords[1] + width / 2, p.coords[2] - height / 2);
	Vec4 v2(p.coords[0] + width / 2, p.coords[1] + width / 2, p.coords[2] - height / 2);
	Vec4 v3(p.coords[0] + width / 2, p.coords[1] - width / 2, p.coords[2] - height / 2);

	Vec4 v4(p.coords[0] - width / 2, p.coords[1] - width / 2, p.coords[2] + height / 2);
	Vec4 v5(p.coords[0] - width / 2, p.coords[1] + width / 2, p.coords[2] + height / 2);
	Vec4 v6(p.coords[0] + width / 2, p.coords[1] + width / 2, p.coords[2] + height / 2);
	Vec4 v7(p.coords[0] + width / 2, p.coords[1] - width / 2, p.coords[2] + height / 2);
	//Botten
	cube->addTriangleToMesh(new Triangle(v0, v1, v3, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v1, v2, v3, m.diff_col));
	//Toppen
	cube->addTriangleToMesh(new Triangle(v4, v7, v6, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v4, v6, v5, m.diff_col));
	//front
	cube->addTriangleToMesh(new Triangle(v1, v4, v5, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v1, v0, v4, m.diff_col));
	//Back
	cube->addTriangleToMesh(new Triangle(v7, v3, v2, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v2, v6, v7, m.diff_col));
	//Left
	cube->addTriangleToMesh(new Triangle(v1, v5, v6, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v1, v6, v2, m.diff_col));
	//Right
	cube->addTriangleToMesh(new Triangle(v7, v4, v0, m.diff_col));
	cube->addTriangleToMesh(new Triangle(v7, v0, v3, m.diff_col));

	objectList.push_back(std::shared_ptr<Object>(cube));
}
void Scene::createRoom(const Material& m)
{
	Mesh* room = new Mesh(m);
	//Tak
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(-3, 0, 5), Vec4(0, 6, 5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(0, 6, 5), Vec4(10, 6, 5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(10, 6, 5), Vec4(13, 0, 5), ColorDbl(255,255, 255)));

	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(13, 0, 5), Vec4(10, -6, 5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(10, -6, 5), Vec4(0, -6, 5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(0, -6, 5), Vec4(-3, 0, 5), ColorDbl(255, 255, 255)));

	//Golv		 
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(0, 6, -5), Vec4(-3, 0, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(10, 6, -5), Vec4(0, 6, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(13, 0, -5), Vec4(10, 6, -5), ColorDbl(255, 255, 255)));

	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(10, -6, -5), Vec4(13, 0, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(0, -6, -5), Vec4(10, -6, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(-3, 0, -5), Vec4(0, -6, -5), ColorDbl(255, 255, 255)));

	//Vägg Upp
	room->addTriangleToMesh(new Triangle(Vec4(0, 6, 5), Vec4(0, 6, -5), Vec4(10, 6, -5), ColorDbl(255, 0, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(0, 6, 5), Vec4(10, 6, -5), Vec4(10, 6, 5), ColorDbl(255, 0, 0)));
	//Vägg Upp Hö
	room->addTriangleToMesh(new Triangle(Vec4(10, 6, 5), Vec4(10, 6, -5), Vec4(13, 0, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(10, 6, 5), Vec4(13, 0, -5), Vec4(13, 0, 5), ColorDbl(255, 255, 255)));
	//Vägg Upp-Vä
	room->addTriangleToMesh(new Triangle(Vec4(-3, 0, 5), Vec4(-3, 0, -5), Vec4(0, 6, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(-3, 0, 5), Vec4(0, 6, -5), Vec4(0, 6, 5), ColorDbl(255, 255, 255)));

	//Vägg Ner	 
	room->addTriangleToMesh(new Triangle(Vec4(10, -6, 5), Vec4(10, -6, -5), Vec4(0, -6, -5), ColorDbl(0, 255, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(10, -6, 5), Vec4(0, -6, -5), Vec4(0, -6, 5), ColorDbl(0, 255, 0)));
	//Vägg Ner Hö
	room->addTriangleToMesh(new Triangle(Vec4(13, 0, 5), Vec4(13, 0, -5), Vec4(10, -6, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(13, 0, 5), Vec4(10, -6, -5), Vec4(10, -6, 5), ColorDbl(255, 255, 255)));
	//Vägg Ner Vä
	room->addTriangleToMesh(new Triangle(Vec4(0, -6, 5), Vec4(0, -6, -5), Vec4(-3, 0, -5), ColorDbl(255, 255, 255)));
	room->addTriangleToMesh(new Triangle(Vec4(0, -6, 5), Vec4(-3, 0, -5), Vec4(-3, 0, 5), ColorDbl(255, 255, 255)));

	objectList.push_back(std::shared_ptr<Object>(room));

}