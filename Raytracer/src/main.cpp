#include "Includer.h"
#include "Scene.h"
#include "Camera.h"

int main() {


	//Classes/Structs:	Scene, Triangle, Ray, Direction, 
	//					ColorDbl, Pixel, Camera, Vertex

	//Subclasses? :	Sphere, tetrahedral - contains Triangles
	std::cout << "Hello world"<<std::endl;

	//Vertex T = ray.ps - v0;
	//Vertex E1 = v1 - v0;
	//Vertex E2 = v2 - v0;
	//Vertex D = ray.pe - ray.ps;

	//Vertex P = D.crossProduct(E2);
	//Vertex Q = T.crossProduct(E1);

	//float u = P.dotProduct(T) / P.dotProduct(E1);

	//glm::vec3 v0 = { 5, 1, 5 };
	//glm::vec3 v1 = { 0, 2, 4 };
	//glm::vec3 v2 = { 0, 1, 5 };

	//float x = v0[0];
	//float y = v0[1];
	//float z = v0[2];

	//float result = glm::dot(v0,v1);
	//glm::vec3 rescross = glm::cross(v0, v1);

	//std::cout << rescross[0] <<", "<< rescross[1] <<", "<< rescross[2];

	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render(theScene);
	camera.createImage();

	return 0;
}