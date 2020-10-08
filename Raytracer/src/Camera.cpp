#pragma once
#include "Camera.h"

Camera::Camera() {
	for (int i = 0; i < height; ++i) {
		pixel_array[i] = new Pixel[width];
	}
}
Camera::~Camera() {
	for (int i = 0; i < height; i++)
		delete[] pixel_array[i];
	delete[] pixel_array;
}

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
		percentage = (static_cast<float>((i + 1)) / width) * 100;
		LOG("\rRendering: " << percentage << std::fixed << std::setprecision(5) << std::left << std::setw(7) << "%");
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
Vec4 Camera::calcRandomHemiDir(const Vec4& N)//send in r1 & r2 too
{


	//1. get random destibution floats
	//2. use the floats to transform back to world coords
	//3. return the direction

	return Vec4(1, 2, 3, 4);
}
bool Camera::objectIntersect(std::list<Object*>& objectList, Ray& ray, Object*& hitObject, float& t_closest)
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
	if (hitObject == nullptr)
		return false;

	return true;
}
ColorDbl Camera::tracePath(std::list<Object*>& objectList, std::list<Light*>& lightList, Ray& ray)
{
	ColorDbl col;
	Object* hitObject = nullptr;
	//loop through objects instead of meshes (includes spheres)
	float t_temp = INFINITY_FLOAT;
	if (objectIntersect(objectList, ray, hitObject, t_temp))
	{
		//Do everthing here

		Material hitMat = hitObject->getMaterial();

		Vec4 dir = ray.getDirection().normalize();
		Vec4 norm_hit = ray.getHitNormal().normalize();

		Vec4 refl_dir = dir.reflect(norm_hit).normalize(); //perfect reflection (whitted)
		


		Vec4 hitPoint = ray.getOffsetEndPointAlongNormal(EPSILON);

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
			//Direct lighting:
			for (std::list<Light*>::iterator lights = lightList.begin(); lights != lightList.end(); lights++)
			{
				Vec4 lightDir = (*lights)->getPosition() - hitPoint;
				Ray shadow_ray{ hitPoint, lightDir.normalize() };

				float angleIntensity = lightDir.normalize().dotProduct(norm_hit);

				float lightDistance = lightDir.dotProduct(lightDir);

				Object* shadowObject = nullptr;
				float t_shadow = INFINITY_FLOAT;
				/*
				TODO: 
					change the direct lighting to use area lights instead of point.
				*/
				//check normal of object compared with shadowray direction and rule out if its impossible to hit.
				if (angleIntensity > EPSILON)
				{
					//if object is not in shadow -> calculate radiance from the point.
					if (!(objectIntersect(objectList, shadow_ray, shadowObject, t_shadow) && t_shadow * t_shadow < lightDistance))
					{
						radiance += (*lights)->getIntensity() * angleIntensity;

					}
				}
			}
			/*
				TODO: reflective diffuse
				radiance is the direct lighting here

				loop and calculate indirect light (GI)
				loop how many times? (how many rays to cast through the hemisphere)

				sum the direct and indirect light at the end
				lastly divide by pdf
			*/
			//Monte Carlo things:
			

			//local coordinate system directions for hitpoint:
			//Vec4 X = Vec4(norm_hit.coords[2], 0.0f, -norm_hit.coords[0]).normalize();
			//Vec4 Y = norm_hit.crossProduct(X);
			//Vec4 Z = norm_hit;

			//Vec4 refl_dir = calcRandomHemiDir(X,Y,Z); //change to montecarlo reflection 
			//***********************
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
		ColorDbl** log_array = new ColorDbl * [height];
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