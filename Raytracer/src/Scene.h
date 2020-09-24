#pragma once
#include "Includer.h"
#include "Triangle.h"
#include "Mesh.h"
class Scene {
public:
	Scene() = default;
	~Scene()
	{
		for (std::list<Mesh*>::iterator it = meshList.begin(); it != meshList.end(); ++it) {
			delete* it;
		}
		meshList.clear();
	}
	void createScene();
	void createRoom();
	std::list<Mesh*> getMeshList() const;
private:
	std::list<Mesh*> meshList;

};
std::list<Mesh*> Scene::getMeshList() const{
	return meshList;
}
void Scene::createScene() {
	//Tak
	createRoom();
	//TODO:
	//Skapa en funktion f�r mittpunkt skapning av tetra och kuber


	Mesh* tetra = new Mesh();
	//Botten
	tetra->addTriangleToMesh(new Triangle(Vertex(6, 0.5, 0), Vertex(7, 0, 0), Vertex(6, -0.5, 0), ColorDbl(255, 255, 200)));
	//Mot kameran
	tetra->addTriangleToMesh(new Triangle(Vertex(6.5, 0, 1), Vertex(6, 0.5, 0), Vertex(6, -0.5, 0), ColorDbl(255, 255, 200)));
	tetra->addTriangleToMesh(new Triangle(Vertex(6.5, 0, 1), Vertex(7, 0, 0), Vertex(6, 0.5, 0), ColorDbl(255, 255, 200)));
	tetra->addTriangleToMesh(new Triangle(Vertex(6.5, 0, 1), Vertex(6, -0.5, 0), Vertex(7, 0, 0), ColorDbl(255, 255, 200)));
	meshList.push_back(tetra);
	//Tetrahedral
	
	//createTetrahedral();

}
void Scene::createRoom()
{
	Mesh* room = new Mesh();
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(-3, 0, 5), Vertex(0, 6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(0, 6, 5), Vertex(10, 6, 5), ColorDbl(255, 0, 0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(10, 6, 5), Vertex(13, 0, 5), ColorDbl(255,0,0)));
				 
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(13, 0, 5), Vertex(10, -6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(10, -6, 5), Vertex(0, -6, 5), ColorDbl(255,0,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, 5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(255, 0, 0)));
				 
	//Golv		 
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(0, 6, -5), Vertex(-3, 0, -5), ColorDbl(0, 255, 0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(10, 6, -5), Vertex(0, 6, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(13, 0, -5), Vertex(10, 6, -5), ColorDbl(0,255,0)));
				 
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(10, -6, -5), Vertex(13, 0, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(0, -6, -5), Vertex(10, -6, -5), ColorDbl(0,255,0)));
	room->addTriangleToMesh(new Triangle(Vertex(5, 0, -5), Vertex(-3, 0, -5), Vertex(0, -6, -5), ColorDbl(0,255,0)));
				 
	//V�gg Upp	 
	room->addTriangleToMesh(new Triangle(Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(10, 6, -5), ColorDbl(0,255,255)));
	room->addTriangleToMesh(new Triangle(Vertex(0, 6, 5), Vertex(10, 6, -5), Vertex(10, 6, 5), ColorDbl(0,255,255)));
	//V�gg Upp H�
	room->addTriangleToMesh(new Triangle(Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(13, 0, -5), ColorDbl(128, 128, 128)));
	room->addTriangleToMesh(new Triangle(Vertex(10, 6, 5), Vertex(13, 0, -5), Vertex(13, 0, 5), ColorDbl(128, 128, 128)));
	//V�gg Upp-V�
	room->addTriangleToMesh(new Triangle(Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(0, 6, -5), ColorDbl(255,0,255)));
	room->addTriangleToMesh(new Triangle(Vertex(-3, 0, 5), Vertex(0, 6, -5), Vertex(0, 6, 5), ColorDbl(255,0,255)));
				 
	//V�gg Ner	 
	room->addTriangleToMesh(new Triangle(Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(0, -6, -5), ColorDbl(255, 255, 0)));
	room->addTriangleToMesh(new Triangle(Vertex(10, -6, 5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(255, 255, 0)));
	//V�gg Ner H�
	room->addTriangleToMesh(new Triangle(Vertex(13, 0, 5), Vertex(13, 0, -5), Vertex(10, -6, -5), ColorDbl(255, 128, 0)));
	room->addTriangleToMesh(new Triangle(Vertex(13, 0, 5), Vertex(10, -6, -5), Vertex(10, -6, 5), ColorDbl(255, 128, 0)));
	//V�gg Ner V�
	room->addTriangleToMesh(new Triangle(Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(-3, 0, -5), ColorDbl(128,0,255)));
	room->addTriangleToMesh(new Triangle(Vertex(0, -6, 5), Vertex(-3, 0, -5), Vertex(-3, 0, 5), ColorDbl(128,0,255)));

	meshList.push_back(room);
	
}