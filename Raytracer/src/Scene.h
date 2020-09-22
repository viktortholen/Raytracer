#pragma once
#include "Includer.h"
#include "Triangle.h"
class Scene {
public:
	Scene() = default;
	~Scene()
	{
		for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); ++it) {
			delete* it;
		}
		triangleList.clear();
	}
	void createScene();
	std::list<Triangle*> getTriangleList() const;
private:
	std::list<Triangle*> triangleList;

};
std::list<Triangle*> Scene::getTriangleList() const{
	return triangleList;
}
void Scene::createScene() {
	//Tak
	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(-3, 0, 5), Vertex(0, 6, 5), ColorDbl(255,0,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, 6, 5), Vertex(10, 6, 5), ColorDbl(255, 0, 0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, 6, 5), Vertex(13, 0, 5), ColorDbl(255,0,0)));

	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(13, 0, 5), Vertex(10, -6, 5), ColorDbl(255,0,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, -6, 5), Vertex(0, -6, 5), ColorDbl(255,0,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, -6, 5), Vertex(-3, 0, 5), ColorDbl(255, 0, 0)));

	//Golv
	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(0, 6, -5), Vertex(-3, 0, -5), ColorDbl(0, 255, 0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(10, 6, -5), Vertex(0, 6, -5), ColorDbl(0,255,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(13, 0, -5), Vertex(10, 6, -5), ColorDbl(0,255,0)));

	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(10, -6, -5), Vertex(13, 0, -5), ColorDbl(0,255,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(0, -6, -5), Vertex(10, -6, -5), ColorDbl(0,255,0)));
	triangleList.push_back(new Triangle(Vertex(5, 0, -5), Vertex(-3, 0, -5), Vertex(0, -6, -5), ColorDbl(0,255,0)));

	//Vägg Upp
	triangleList.push_back(new Triangle(Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(10, 6, -5), ColorDbl(0,255,255)));
	triangleList.push_back(new Triangle(Vertex(0, 6, 5), Vertex(10, 6, -5), Vertex(10, 6, 5), ColorDbl(0,255,255)));
	//Vägg Upp Höger
	triangleList.push_back(new Triangle(Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(13, 0, -5), ColorDbl(128, 128, 128)));
	triangleList.push_back(new Triangle(Vertex(10, 6, 5), Vertex(13, 0, -5), Vertex(13, 0, 5), ColorDbl(128, 128, 128)));
	//Vägg Upp-Vänster
	triangleList.push_back(new Triangle(Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(0, 6, -5), ColorDbl(255,0,255)));
	triangleList.push_back(new Triangle(Vertex(-3, 0, 5), Vertex(0, 6, -5), Vertex(0, 6, 5), ColorDbl(255,0,255)));

	//Vägg Ner
	triangleList.push_back(new Triangle(Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(0, -6, -5), ColorDbl(255, 255, 0)));
	triangleList.push_back(new Triangle(Vertex(10, -6, 5), Vertex(0, -6, -5), Vertex(0, -6, 5), ColorDbl(255, 255, 0)));
	//Vägg Ner Höger
	triangleList.push_back(new Triangle(Vertex(13, 0, 5), Vertex(13, 0, -5), Vertex(10, -6, -5), ColorDbl(255, 128, 0)));
	triangleList.push_back(new Triangle(Vertex(13, 0, 5), Vertex(10, -6, -5), Vertex(10, -6, 5), ColorDbl(255, 128, 0)));
	//Vägg Ner Vänster
	triangleList.push_back(new Triangle(Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(-3, 0, -5), ColorDbl(128,0,255)));
	triangleList.push_back(new Triangle(Vertex(0, -6, 5), Vertex(-3, 0, -5), Vertex(-3, 0, 5), ColorDbl(128,0,255)));

	//Tetrahedral
	
	//createTetrahedral();

}