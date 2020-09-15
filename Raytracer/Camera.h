#pragma once
#include "Includer.h"
#include "Pixel.h"

class Camera {
public:
	Camera() = default;
	
	void render() {

	}
	void createImage() {

	}


private:
	Pixel pixel_array[800][800];
	Vertex e1, e2;
	bool switchEyePoint = 0;

};

