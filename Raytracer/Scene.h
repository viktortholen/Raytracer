#pragma once
#include "Includer.h"
#include "Triangle.h"
class Scene {
public:
	Scene() = default;

	void createScene() {
		//Tak
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(-3, 0, 5), Vertex(0, 6, 5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, 6, 5), Vertex(10, 6, 5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, 6, 5), Vertex(13, 0, 5)));

		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(13, 0, 5), Vertex(10, -6, 5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, -6, 5), Vertex(0, -6, 5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, -6, 5), Vertex(-3, 0, 5)));

		//Golv
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, 6, 5), Vertex(-3, 0, -5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, 6, 5), Vertex(0, 6, -5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(13, 0, 5), Vertex(10, 6, -5)));

		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(10, -6, 5), Vertex(13, 0, -5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(0, -6, 5), Vertex(10, -6, -5)));
		triangleList.push_back(new Triangle(Vertex(5, 0, 5), Vertex(-3, 0, 5), Vertex(0, -6, -5)));

		//Vägg Upp
		triangleList.push_back(new Triangle(Vertex(0, 6, 5), Vertex(0, 6, -5), Vertex(10, 6, -5)));
		triangleList.push_back(new Triangle(Vertex(0, 6, 5), Vertex(10, 6, -5), Vertex(10, 6, 5)));
		//Vägg Upp-Vänster
		triangleList.push_back(new Triangle(Vertex(-3, 0, 5), Vertex(-3, 0, -5), Vertex(0, 6, -5)));
		triangleList.push_back(new Triangle(Vertex(-3, 0, 5), Vertex(0, 6, -5), Vertex(0, 6, 5)));
		//Vägg Upp Höger
		triangleList.push_back(new Triangle(Vertex(10, 6, 5), Vertex(10, 6, -5), Vertex(13, 0, -5)));
		triangleList.push_back(new Triangle(Vertex(10, 6, 5), Vertex(13, 0, -5), Vertex(13, 0, 5)));

		//Vägg Ner
		triangleList.push_back(new Triangle(Vertex(10, -6, 5), Vertex(10, -6, -5), Vertex(0, -6, -5)));
		triangleList.push_back(new Triangle(Vertex(10, -6, 5), Vertex(0, -6, -5), Vertex(0, -6, 5)));
		//Vägg Ner Höger
		triangleList.push_back(new Triangle(Vertex(13, 0, 5), Vertex(13, 0, -5), Vertex(10, -6, -5)));
		triangleList.push_back(new Triangle(Vertex(13, 0, 5), Vertex(10, -6, -5), Vertex(10, -6, 5)));
		//Vägg Ner Vänster
		triangleList.push_back(new Triangle(Vertex(0, -6, 5), Vertex(0, -6, -5), Vertex(-3, 0, -5)));
		triangleList.push_back(new Triangle(Vertex(0, -6, 5), Vertex(-3, 0, -5), Vertex(-3, 0, 5)));

	}
private:
	std::list<Triangle*> triangleList;



};