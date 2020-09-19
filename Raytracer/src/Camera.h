#pragma once
#include "Includer.h"
#include "Pixel.h"
#include "Ray.h"

#define LOG(x) std::cout << x;

class Camera {
public:
	Camera() {
		for (int i = 0; i < resolution_z; ++i) {
			pixel_array[i] = new Pixel[resolution_y];
		}
	}
	~Camera() {
		delete[] pixel_array;
	}

	void render();
	void createImage();


private:
	const int resolution_y = 800;
	const int resolution_z = 800;
	
	Pixel** pixel_array = new Pixel* [resolution_z];

	const Vertex e1{ -1,0,0 };
	const Vertex e2{ -2,0,0 };
	bool switchEyePoint = 0;

};

void Camera::render() {

	//for loop för att gå igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (Camera::resolution_y / 2) + 1;
	int quad_size_z = (Camera::resolution_z / 2) + 1;
	float delta = static_cast<float>(2 / resolution_y);
	float percentage;
	for (int i = 0; i < resolution_y; i++)
	{
		//LOG progress:
		percentage = (static_cast<float>((i + 1)) / resolution_y)* 100;
		LOG("\rRendering: " << percentage <<std::fixed<<std::setprecision(0)<<std::left<<std::setw(7)<< "%");
		/******************************************/


		for (int j = 0; j < resolution_z; j++)
		{
			float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			Vertex pixelIntersection{ 0.0, (i - quad_size_y + ry)*delta, (j-quad_size_z + rz)*delta};
			Ray ray{ e1, pixelIntersection};
			
			
		}
	}
}

