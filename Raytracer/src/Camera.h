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
	bool objectIntersect(std::list<Object*>& objectList, std::list<Light*>& lightList, Ray& ray, Object*& hitObject, float& t_closest);

private:
	const int width = 800;
	const int height = 800;
	const float EPSILON = 0.00001f;
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
			Vec4 dir = pixelIntersection - e1;
			Ray ray{ e1, dir.normalize() };
			ColorDbl col = tracePath(objectList, lightList, ray);
			pixel_array[i][j].setColor(col);
		} 
	}
}
bool Camera::objectIntersect(std::list<Object*>& objectList, std::list<Light*>& lightList, Ray& ray, Object*& hitObject, float &t_closest)
{
	hitObject = nullptr;
	float obj_closest = INFINITY_FLOAT;
	for (std::list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		if ((*it)->castRay(ray, t_closest) && t_closest < obj_closest) //object is hit
		{
			hitObject = (*it);
			obj_closest = t_closest;
		}
	}
	if (hitObject == nullptr )
		return false;

	return true;
}
ColorDbl Camera::tracePath(std::list<Object*> &objectList, std::list<Light*> &lightList, Ray& ray)
{
	ColorDbl col;
	Object* hitObject = nullptr;
	//loop through objects instead of meshes (includes spheres)
	float t_temp = INFINITY_FLOAT;
	if (objectIntersect(objectList, lightList, ray, hitObject, t_temp))
	{
		//Do everthing here

		Material hitMat = hitObject->getMaterial();

		Vec4 dir = ray.getDirection().normalize();
		//Vec4 norm_hit = ray.getTriangle()->getNormal().normalize(); //change to object normal to include spheres
		Vec4 norm_hit = ray.getHitNormal().normalize(); //change to object normal to include spheres
		Vec4 refl_dir = dir.reflect(norm_hit).normalize();

		Vec4 hitPoint = ray.pe + (EPSILON * norm_hit);
		switch (hitMat.type)
		{
			case(MaterialType::REFLECTIVE_LAMBERTIAN): //perfect mirror
			{


				//trace new ray in the reflection direction:
				Ray refl_ray{ hitPoint, refl_dir };

				col = tracePath(objectList, lightList, refl_ray);
				break;

			}
			case(MaterialType::DIFFUSE_LAMBERTIAN): //
			{
				float radiance = 0.0f;
				//loop through lights
				for (std::list<Light*>::iterator lights = lightList.begin(); lights != lightList.end(); lights++)
				{
					Vec4 lightDir = (*lights)->getPosition() - hitPoint;
					Ray shadow_ray{ hitPoint, lightDir.normalize() };
					
					float angleIntensity = std::max(0.f, lightDir.normalize().dotProduct(norm_hit));

					float lightDistance = lightDir.dotProduct(lightDir);

					Object* shadowObject = nullptr;
					float t_shadow = INFINITY_FLOAT;
					
					//norm_hit.printCoords();
					//check normal of object compared with shadowray direction and rule out if its impossible to hit.
					bool canHit = (norm_hit.dotProduct(lightDir.normalize()) > EPSILON);
					if (canHit)
					{
						//if object is not in shadow -> calculate radiance from the point.
						if (!(objectIntersect(objectList, lightList, shadow_ray, shadowObject, t_shadow) &&  t_shadow * t_shadow < lightDistance))
						{
							//std::cout << t_shadow;
							radiance += (*lights)->getIntensity() * angleIntensity;
						}
						//col = ColorDbl(255, 255, 255);
					}
					else {
						//col = ColorDbl(50, 50, 50);
						//norm_hit.printCoords(); //wrong normals!
						//lightDir.normalize().printCoords(); //correct
					}

				}
				//std::cout << radiance<<std::endl;
				//col = ray.endPointTriangle->getColor();
				col = hitMat.diff_col * radiance;
				break;
			}
		}
	}
	

	return col;


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