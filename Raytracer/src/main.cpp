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

	//glm::vecsize v0 = { 5, 1, 5 };
	//glm::vecsize v1 = { 0, 2, 4 };
	//glm::vecsize v2 = { 0, 1, 5 };

	//float x = v0[0];
	//float y = v0[1];
	//float z = v0[2];

	//float result = glm::dot(v0,v1);
	//glm::vecsize rescross = glm::cross(v0, v1);

	//std::cout << rescross[0] <<", "<< rescross[1] <<", "<< rescross[2];
	//const int size = 3;
	//int** pixel_array = new int*[size];
	//for (int i = 0; i < size; ++i) {
	//	pixel_array[i] = new int[size];
	//}

	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j) {
	//		pixel_array[i][j] = i + j;
	//	}
	//}


	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j) {

	//		std::cout  << " "<<*pixel_array[i, j];
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << std::endl << pixel_array[0][2];

	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render(theScene);
	camera.createImage("picture.ppm", "LOG");

	return 0;
}
