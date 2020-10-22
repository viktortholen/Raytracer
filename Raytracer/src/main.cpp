#include "Includer.h"
#include "Scene.h"
#include "Camera.h"

int main() {

	Scene theScene{};
	theScene.createScene();

	Camera camera{};
	camera.render(theScene);
	camera.createImage("picture.ppm", "LINEAR");

	return 0;
}
