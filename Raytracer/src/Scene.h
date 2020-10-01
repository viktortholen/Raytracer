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
	~Scene()
	{
		for (std::list<Object*>::iterator it = objectList.begin(); it != objectList.end(); ++it) {
			delete* it;
		}
		objectList.clear();
	}
	void createScene();
	void createRoom(const Material& m);

	void createTetra(const Vec4& p, const float& size, const Material& m);
	void createSphere(const Vec4& p, const float& size, const Material& m);
	void createCube(const Vec4& p, const float& size, const Material& m);

	std::list<Object*> getObjectList() const;
	std::list<Light*> getLightList() const;
private:
	std::list<Object*> objectList;
	std::list<Light*> lightList;

};
std::list<Object*> Scene::getObjectList() const{
	return objectList;
}
std::list<Light*> Scene::getLightList() const{
	return lightList;
}
void Scene::createScene() {
	Material diff_mat{ MaterialType::DIFFUSE_LAMBERTIAN, ColorDbl(245,52,12) };
	Material refl_mat{ MaterialType::DIFFUSE_LAMBERTIAN, ColorDbl(0,250,12) };

	//Tak
	createRoom(diff_mat);

	createTetra(Vec4(6,0,-2), 2.0f, refl_mat);
	createCube(Vec4(6,-2,-2), 2.0f, refl_mat);
	createSphere(Vec4(6, 1, 1), 2.5f, refl_mat);

	Light* light = new Light(Vec4(5,0,4.9f), 1.0f);
	lightList.push_back(light);

}
void Scene::createTetra(const Vec4& p, const float& size, const Material& m)
{
	Mesh* tetra = new Mesh(m);
	//Botten
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0]-size/2, p.coords[1]+size/2, p.coords[2]-size/2), Vec4(p.coords[0]+size/2, p.coords[1], p.coords[2]-size/2), Vec4(p.coords[0]-size/2, p.coords[1]-size/2, p.coords[2]-size/2), ColorDbl(255, 255, 200)));
	//Mot kameran
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2]+size/2), Vec4(p.coords[0]-size/2, p.coords[1]+size/2, p.coords[2]-size/2), Vec4(p.coords[0]-size/2, p.coords[1]-size/2, p.coords[2]-size/2), ColorDbl(255, 255, 200)));
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2]+size/2), Vec4(p.coords[0]-size/2, p.coords[1]-size/2, p.coords[2]-size/2), Vec4(p.coords[0]+size/2, p.coords[1], p.coords[2]-size/2), ColorDbl(255, 255, 200)));
	tetra->addTriangleToMesh(new Triangle(Vec4(p.coords[0], p.coords[1], p.coords[2]+size/2), Vec4(p.coords[0]+size/2, p.coords[1], p.coords[2]-size/2), Vec4(p.coords[0]-size/2, p.coords[1]+size/2, p.coords[2]-size/2), ColorDbl(255, 255, 200)));
	objectList.push_back(tetra);
}
void Scene::createSphere(const Vec4& p, const float& size, const Material& m)
{
	Sphere* sphere = new Sphere(0.4f, p, m);
	objectList.push_back(sphere);
}
void Scene::createCube(const Vec4& p, const float& size, const Material& m)
{
	Mesh* cube = new Mesh(m);

	Vec4 v0(p.coords[0]-size / 2, p.coords[1]-size / 2, p.coords[2]-size / 2);
	Vec4 v1(p.coords[0]-size / 2, p.coords[1]+size / 2, p.coords[2]-size / 2);
	Vec4 v2(p.coords[0]+size / 2, p.coords[1]+size / 2, p.coords[2]-size / 2);
	Vec4 v3(p.coords[0]+size / 2, p.coords[1]-size / 2, p.coords[2]-size / 2);	
	
	Vec4 v4(p.coords[0]-size / 2, p.coords[1]-size / 2, p.coords[2]+size / 2);
	Vec4 v5(p.coords[0]-size / 2, p.coords[1]+size / 2, p.coords[2]+size / 2);
	Vec4 v6(p.coords[0]+size / 2, p.coords[1]+size / 2, p.coords[2]+size / 2);
	Vec4 v7(p.coords[0]+size / 2, p.coords[1]-size / 2, p.coords[2]+size / 2);
	//Botten
	cube->addTriangleToMesh(new Triangle(v0, v1, v3, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v1, v2, v3, ColorDbl(255, 255, 200)));
	//Toppen
	cube->addTriangleToMesh(new Triangle(v4, v7, v6, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v5, v4, v6, ColorDbl(255, 255, 200)));
	//front
	cube->addTriangleToMesh(new Triangle(v1, v0, v4, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v1,v4,v5, ColorDbl(255, 255, 200)));
	//Back
	cube->addTriangleToMesh(new Triangle(v7,v3, v2, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v2,v6,v7, ColorDbl(255, 255, 200)));
	//Left
	cube->addTriangleToMesh(new Triangle(v1,v5,v6, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v1,v6,v2, ColorDbl(255, 255, 200)));
	//Right
	cube->addTriangleToMesh(new Triangle(v7,v4,v0, ColorDbl(255, 255, 200)));
	cube->addTriangleToMesh(new Triangle(v7,v0,v3, ColorDbl(255, 255, 200)));

	objectList.push_back(cube);
}
void Scene::createRoom(const Material &m)
{
	Mesh* room = new Mesh(m);
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(-3, 0, 5), Vec4(0, 6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(0, 6, 5), Vec4(10, 6, 5), ColorDbl(255, 0, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(10, 6, 5), Vec4(13, 0, 5), ColorDbl(255,0,0)));
				 
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(13, 0, 5), Vec4(10, -6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(10, -6, 5), Vec4(0, -6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, 5), Vec4(0, -6, 5), Vec4(-3, 0, 5), ColorDbl(255, 0, 0)));
				 
	//Golv		 
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(0, 6, -5), Vec4(-3, 0, -5), ColorDbl(0, 255, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(10, 6, -5), Vec4(0, 6, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(13, 0, -5), Vec4(10, 6, -5), ColorDbl(0,255,0)));
				 
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(10, -6, -5), Vec4(13, 0, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(0, -6, -5), Vec4(10, -6, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vec4(5, 0, -5), Vec4(-3, 0, -5), Vec4(0, -6, -5), ColorDbl(0,255,0)));
				 
	//Vägg Upp
	room->addTriangleToMesh(new Triangle(Vec4(0, 6, 5), Vec4(0, 6, -5), Vec4(10, 6, -5), ColorDbl(0,255,255)));
	room->addTriangleToMesh(new Triangle(Vec4(0, 6, 5), Vec4(10, 6, -5), Vec4(10, 6, 5), ColorDbl(0,255,255)));
	//Vägg Upp Hö
	room->addTriangleToMesh(new Triangle(Vec4(10, 6, 5), Vec4(10, 6, -5), Vec4(13, 0, -5), ColorDbl(128, 128, 128)));
	room->addTriangleToMesh(new Triangle(Vec4(10, 6, 5), Vec4(13, 0, -5), Vec4(13, 0, 5), ColorDbl(128, 128, 128)));
	//Vägg Upp-Vä
	room->addTriangleToMesh(new Triangle(Vec4(-3, 0, 5), Vec4(-3, 0, -5), Vec4(0, 6, -5), ColorDbl(255,0,255)));
	room->addTriangleToMesh(new Triangle(Vec4(-3, 0, 5), Vec4(0, 6, -5), Vec4(0, 6, 5), ColorDbl(255,0,255)));
				 
	//Vägg Ner	 
	room->addTriangleToMesh(new Triangle(Vec4(10, -6, 5), Vec4(10, -6, -5), Vec4(0, -6, -5), ColorDbl(255, 255, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(10, -6, 5), Vec4(0, -6, -5), Vec4(0, -6, 5), ColorDbl(255, 255, 0)));
	//Vägg Ner Hö
	room->addTriangleToMesh(new Triangle(Vec4(13, 0, 5), Vec4(13, 0, -5), Vec4(10, -6, -5), ColorDbl(255, 128, 0)));
	room->addTriangleToMesh(new Triangle(Vec4(13, 0, 5), Vec4(10, -6, -5), Vec4(10, -6, 5), ColorDbl(255, 128, 0)));
	//Vägg Ner Vä
	room->addTriangleToMesh(new Triangle(Vec4(0, -6, 5), Vec4(0, -6, -5), Vec4(-3, 0, -5), ColorDbl(128,0,255)));
	room->addTriangleToMesh(new Triangle(Vec4(0, -6, 5), Vec4(-3, 0, -5), Vec4(-3, 0, 5), ColorDbl(128,0,255)));

	objectList.push_back(room);
	
}