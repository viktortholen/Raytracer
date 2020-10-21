#include "Includer.h"
#include "Scene.h"
#include "Camera.h"

int main() {
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";
	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render(theScene);
	camera.createImage("picture.ppm", "LOG");

	return 0;
}
