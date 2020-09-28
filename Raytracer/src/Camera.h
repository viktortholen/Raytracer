#pragma once
#include "Includer.h"
#include "Pixel.h"
#include "Ray.h"
#include "Scene.h"
#include "Object.h"
#include "Light.h"
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
	void createImage(std::string filename, std::string colorSpace);
	void openImage(std::string filename);
	ColorDbl tracePath(std::list<Object*> &objectList, std::list<Light*> &lightList, Ray& ray);

private:
	const int width = 800;
	const int height = 800;
	const float INFINITY_FLOAT = std::numeric_limits<float>::max();

	Pixel** pixel_array = new Pixel* [height];
	const Vec4 e1{ -1,0,0 };
	const Vec4 e2{ -2,0,0 };
	bool eyePoint = 0;

};

void Camera::render(const Scene& scene) {

	//for loop för att gå igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (width / 2) + 1;
	int quad_size_z = (height / 2) + 1;
	float delta = static_cast<float>(2.0 / width);

	float percentage;
	

	std::list<Object*> objectList = scene.getObjectList();
	std::list<Light*> lightList = scene.getLightList();

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
			Vec4 pixelIntersection{ 0.0, (j - quad_size_y + ry) * delta, (i - quad_size_z + rz) * delta };
			Ray ray{ e1, pixelIntersection };
			ColorDbl col = tracePath(objectList, lightList, ray);
			pixel_array[i][j].setColor(col);
		} 
	}
}
ColorDbl Camera::tracePath(std::list<Object*> &objectList, std::list<Light*> &lightList, Ray& ray)
{
	float t_closest = INFINITY_FLOAT;
	float t;
	ColorDbl col;
	//loop through objects instead of meshes (includes spheres)
	for (std::list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		if ((*it)->castRay(ray, t, t_closest, col)) //object is hit
		{
			Object* hitObject = (*it);
			//Do everthing here


		}
	}

	return col;
	//Material m = o->getMaterial();


	//switch (m.type)
	//{
	//	case( MaterialType::DIFFUSE_LAMBERTIAN):
	//	{

	//	}
	//	case(MaterialType::REFLECTIVE_LAMBERTIAN):
	//	{

	//	}
	//}

	//if (m.Ks == 0) {
	//	return m.diff_col;
	//}
	//return col;


}
void Camera::createImage(std::string filename, std::string colorSpace)
{
	std::ofstream img("../Renders/" + filename);
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;
	
	if (colorSpace == "LINEAR")
	{
		LOG("\nCreating image... (LINEAR)\n");
		//find i;

		//For well lit image
		double imax = 0;
		for (int i = height - 1; i >= 0; i--)
		{
			for (int j = width - 1; j >= 0; j--)
			{
				glm::vec3 rgb = pixel_array[i][j].getColor();
				if (rgb[0] > imax)
					imax = rgb[0];
				if (rgb[1] > imax)
					imax = rgb[1];
				if (rgb[2] > imax)
					imax = rgb[2];
			}
		}
		//do this for both!
		for (int i = height - 1; i >= 0; i--)
		{
			for (int j = width - 1; j >= 0; j--)
			{
				glm::vec3 rgb = pixel_array[i][j].getColor();
				int r = static_cast<int>(rgb[0] * (255.99 / imax));
				int g = static_cast<int>(rgb[1] * (255.99 / imax));
				int b = static_cast<int>(rgb[2] * (255.99 / imax));
				img << r << " " << g << " " << b << std::endl;

			}
		}
		//***************
	}
	else if (colorSpace == "LOG")
	{
		LOG("\nCreating image... (LOG)\n");
		ColorDbl** log_array = new ColorDbl*[height];
		for (int i = 0; i < height; ++i) {
			log_array[i] = new ColorDbl[width];
		}

		for (int i = height - 1; i >= 0; i--)
		{
			for (int j = width - 1; j >= 0; j--)
			{
				glm::vec3 rgb = pixel_array[i][j].getColor();
				double sr = sqrt(rgb[0]);
				double sg = sqrt(rgb[1]);
				double sb = sqrt(rgb[2]);

				log_array[i][j] = ColorDbl(sr, sg, sb);
			}
		}
		double imax = 0;
		for (int i = height - 1; i >= 0; i--)
		{
			for (int j = width - 1; j >= 0; j--)
			{
				glm::vec3 rgb = log_array[i][j].getColorVec();
				if (rgb[0] > imax)
					imax = rgb[0];
				if (rgb[1] > imax)
					imax = rgb[1];
				if (rgb[2] > imax)
					imax = rgb[2];
			}
		}
		//do this for both!
		for (int i = height - 1; i >= 0; i--)
		{
			for (int j = width - 1; j >= 0; j--)
			{
				glm::vec3 rgb = log_array[i][j].getColorVec();
				int r = static_cast<int>(rgb[0] * (255.99 / imax));
				int g = static_cast<int>(rgb[1] * (255.99 / imax));
				int b = static_cast<int>(rgb[2] * (255.99 / imax));
				img << r << " " << g << " " << b << std::endl;

			}
		}


		//delete
		for (int i = 0; i < height; i++)
			delete[] log_array[i];
		delete[] log_array;

	}


	
}
void Camera::openImage(std::string filename)
{
	//open the image in a window, how??
}