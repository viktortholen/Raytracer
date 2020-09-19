#include "Includer.h"
#include "Scene.h"
#include "Camera.h"

int main() {


	//Classes/Structs:	Scene, Triangle, Ray, Direction, 
	//					ColorDbl, Pixel, Camera, Vertex

	//Subclasses? :	Sphere, tetrahedral - contains Triangles
	std::cout << "Hello world";


	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render();
	

	return 0;
}