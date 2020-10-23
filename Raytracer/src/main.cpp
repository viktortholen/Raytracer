#include "Includer.h"
#include "Scene.h"
#include "Camera.h"

int main() {

	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render(theScene);

	std::cout << "exiting render" << std::endl;
	camera.createImage("picture.ppm", "LOG");

	return 0;
}
