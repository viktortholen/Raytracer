#pragma once
#include "Includer.h"
#include "Pixel.h"
#include "Ray.h"

#define LOG(x) std::cout << x;

class Camera {
public:
	Camera() {
		for (int i = 0; i < height; ++i) {
			pixel_array[i] = new Pixel[width];
		}
	}
	~Camera() {
		for (int i = 0; i < height; i++)
			delete[] pixel_array[i];
		delete[] pixel_array;
	}

	void render(const Scene& scene);
	void createImage();


private:
	const int width = 800;
	const int height = 800;
	
	Pixel** pixel_array = new Pixel* [height];
	const Vertex e1{ -1,0,0 };
	const Vertex e2{ -2,0,0 };
	bool eyePoint = 0;

};

void Camera::render(const Scene& scene) {

	//for loop f�r att g� igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (width / 2) + 1;
	int quad_size_z = (height / 2) + 1;
	float delta = static_cast<float>(2.0 / width);

	float percentage;

	std::list<Triangle*> trianglelist = scene.getTriangleList();

	for (int i = 0; i < height; i++)
	{
		//LOG progress:
		percentage = (static_cast<float>((i + 1)) / width)* 100;
		LOG("\rRendering: " << percentage <<std::fixed<<std::setprecision(5)<<std::left<<std::setw(7)<< "%");
		/******************************************/


		for (int j = 0; j < width; j++)
		{
			float ry = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float rz = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			Vertex pixelIntersection{ 0.0, (j - quad_size_y + ry)*delta, (i - quad_size_z + rz)*delta};

			Ray ray{ e1, pixelIntersection};
			
			for (std::list<Triangle*>::iterator it = trianglelist.begin(); it != trianglelist.end(); it++)
			{
				if ((*it)->rayIntersection(ray))//f�r tillbaka parametrar och sparar triangeln med l�gst t
				{
					ColorDbl col = (*it)->getColor();
					pixel_array[i][j].setColor(col);
				}
				else
				{
					ColorDbl black{ 0,0,0 };
					pixel_array[i][j].setColor(black);

				}
			}
			//g�r det vi ska med triangeln som tr�ffats
		}
	}
}
void Camera::createImage()
{
	std::ofstream img("picture.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;
	
	LOG("\nCreating image...\n");

	for (int i = height-1; i >= 0; i--)
	{
		for (int j = width-1; j >= 0; j--)
		{
			glm::vec3 rgb = pixel_array[i][j].getColor();

			img << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;

		}
	}
}
