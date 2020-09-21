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
		for (int i = 0; i < resolution_z; i++)
			delete[] pixel_array[i];
		delete[] pixel_array;
	}

	void render(Scene& scene);
	void createImage();


private:
	const int resolution_y = 800;
	const int resolution_z = 800;
	
	Pixel** pixel_array = new Pixel* [resolution_z];

	const Vertex e1{ -1,0,0 };
	const Vertex e2{ -2,0,0 };
	bool eyePoint = 0;

};

void Camera::render(Scene& scene) {

	//for loop för att gå igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (resolution_y / 2) + 1;
	int quad_size_z = (resolution_z / 2) + 1;
	float delta = static_cast<float>(2.0 / resolution_y);

	float percentage;

	std::list<Triangle*> trianglelist = scene.getTriangleList();

	for (int i = 0; i < resolution_y; i++)
	{
		//LOG progress:
		percentage = (static_cast<float>((i + 1)) / resolution_y)* 100;
		LOG("\rRendering: " << percentage <<std::fixed<<std::setprecision(5)<<std::left<<std::setw(7)<< "%");
		/******************************************/


		for (int j = 0; j < resolution_z; j++)
		{
			float ry = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float rz = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			Vertex pixelIntersection{ 0.0, (i - quad_size_y + ry)*delta, (j-quad_size_z + rz)*delta};

			Ray ray{ e1, pixelIntersection};
			
			for (std::list<Triangle*>::iterator it = trianglelist.begin(); it != trianglelist.end(); it++)
			{
				if ((*it)->rayIntersection(ray))
				{
					ColorDbl col = (*it)->getColor();
					std::cout << "TRUE";
					pixel_array[i, j]->setColor(col);
					//set pixel color to triangle color
					break;
				}
			}
			
			
		}
	}
}
void Camera::createImage()
{
	std::ofstream img("picture.ppm");
	img << "P3" << std::endl;
	img << 800 << " " << 800 << std::endl;
	img << "255" << std::endl;

	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 800; j++)
		{
			glm::vec3 rgb = pixel_array[i, j]->getColor();
			//rgb.getColorVec();

			img << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
		}
	}
	//system("open picture.ppm");
}
