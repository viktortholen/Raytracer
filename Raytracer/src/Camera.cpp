#pragma once
#include "Camera.h"

Camera::Camera() {
	pixel_array = new Pixel*[height];
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
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();

	//for loop för att gå igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (width / 2) + 1;
	int quad_size_z = (height / 2) + 1;
	float delta = static_cast<float>(2.0 / width);

	float percentage;
	int samples = 10;
	
	const std::list<Object*> objectList = scene.getObjectList();
	const std::list<Mesh*> lightList = scene.getLightList();

	std::condition_variable cvResults;
	for (int i = 0; i < width; i++)
	{
		//LOG progress:
		percentage = (static_cast<float>((i + 1)) / width) * 100;
		LOG("\rRendering: " << percentage << std::fixed << std::setprecision(5) << std::left << std::setw(7) << "%");
		/******************************************/


		for (int j = 0; j < height; j++)
		{
			//use vector indexes instead of iterators
			//#define INDIRECT
			//#define MULTI_THREADING
			#ifdef MULTI_THREADING

			
			auto fut = std::async(std::launch::async,
				[=, &objectList, &lightList]() -> ColorDbl
					{
						ColorDbl col;
						//LOG("thread id: "<<std::this_thread::get_id()<<std::endl)
						for (int k = 0; k < samples; k++)
						{
							float ry = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
							float rz = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
							Vec4 pixelIntersection{ 0.0, (j - quad_size_y + ry) * delta, (i - quad_size_z + rz) * delta };
							Vec4 dir = pixelIntersection - e1;
							Ray ray{ e1, dir.normalize() };
							col = col + tracePath(objectList, lightList, ray, 0);
						}
						col = col / static_cast<float>(samples);
						//LOG(*at_i << " " << *at_j << std::endl)
						//std::lock_guard<std::mutex> lock(sample_mutex);
						pixel_array[i][j].setColor(col);

						return col;

					});
			{
				std::lock_guard<std::mutex> lock(sample_mutex);
				future_vec.push_back(std::move(fut));
			}


			#else
			ColorDbl col;
			//LOG("thread id: "<<std::this_thread::get_id()<<std::endl)
			for (int k = 0; k < samples; k++)
			{
				float ry = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				float rz = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				Vec4 pixelIntersection{ 0.0, (j - quad_size_y + ry) * delta, (i - quad_size_z + rz) * delta };
				Vec4 dir = pixelIntersection - e1;
				Ray ray{ e1, dir.normalize() };
				col = col + tracePath(objectList, lightList, ray, 0);
			}
			//col = tracePath(objectList, lightList, ray);

			col = col / static_cast<int>(samples);
			//LOG(*at_i << " " << *at_j << std::endl)
			//std::lock_guard<std::mutex> lock(sample_mutex);
			pixel_array[i][j].setColor(col);
			#endif
		}
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;
	std::cout << "\n******************************\n";
	std::cout<<"-Finished rendering-\n Time: " << duration.count() << "s";
	std::cout << "\n******************************\n";

	//for (int i = 0; i < 800; i++)
	//{
	//	for (int j = 0; j < 800; j++)
	//	{
	//		//std::future<ColorDbl> fut = future_vec.at(800 * i + j);
	//		std::future<ColorDbl> *fut = &future_vec[800*i + j];
	//		ColorDbl col = fut->get();
	//		//col.printCoords();
	//		pixel_array[i][j].setColor(col);
	//	}
	//}
}

//ColorDbl Camera::renderSample(const std::list<Object*>* objectList, const std::list<Mesh*>* lightList, Ray* ray, int samples, volatile std::atomic<std::size_t>* at_i, volatile std::atomic<std::size_t>* at_j)
//{
//	ColorDbl col;
//	
//	//LOG("thread id: "<<std::this_thread::get_id()<<std::endl)
//	//for  (int k = 0; k < samples; k++)
//	//{
//	//	col = col + tracePath(*objectList, *lightList, *ray);
//	//}
//	col = tracePath(*objectList, *lightList, *ray);
//	
//	col = col / static_cast<int>(samples);
//	//LOG(*at_i << " " << *at_j << std::endl)
//	std::lock_guard<std::mutex> lock(sample_mutex);
//	pixel_array[*at_i][*at_j].setColor(col);
//
//	return col;
//}
bool Camera::objectIntersect(const std::list<Object*> objectList, Ray& ray, Object*& hitObject, float& t_closest) const
{

		hitObject = nullptr;
		float obj_closest = INFINITY_FLOAT;
		try {

		for (std::list<Object*>::const_iterator it = objectList.cbegin(); it != objectList.cend(); it++)
		{
			if ((*it)->castRay(ray, t_closest) && t_closest < obj_closest) //object is hit
			{
				hitObject = (*it);
				obj_closest = t_closest;
			}
}
		}
		catch (std::bad_array_new_length& e)
		{
			std::cout << "Exception at pixel_array, code:" << e.what() << std::endl;
		}
		if (hitObject == nullptr)
			return false;

		
	
	return true;
}
ColorDbl Camera::tracePath(const std::list<Object*> objectList, const std::list<Mesh*> lightList, Ray& ray, const int& depth)
{
	ColorDbl col;
	Object* hitObject = nullptr;
	//loop through objects instead of meshes (includes spheres)
	float t_temp = INFINITY_FLOAT;
	const int SHADOW_RAY_COUNT = 10;
	if (objectIntersect(objectList, ray, hitObject, t_temp))
	{
		Material hitMat = hitObject->getMaterial();
		ColorDbl hitColor = ray.getColor();
		Vec4 dir = ray.getDirection().normalize();
		Vec4 norm_hit = ray.getHitNormal().normalize();

		Vec4 hitPoint = ray.getOffsetEndPointAlongNormal(EPSILON);
		float T = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (T < 1 - hitMat.absorption || depth < EPSILON)
		{
			switch (hitMat.type)
			{
				case(MaterialType::REFLECTIVE_LAMBERTIAN): //perfect mirror
				{

					Vec4 refl_dir = dir.reflect(norm_hit).normalize(); //perfect reflection (whitted)
					//trace new ray in the reflection direction:
					Ray refl_ray{ hitPoint, refl_dir };

					col = tracePath(objectList, lightList, refl_ray, depth + 1);
					break;
				}
				case(MaterialType::DIFFUSE_LAMBERTIAN): //
				{
					float radiance = 0.0f;
					ColorDbl indirect_col;
					std::random_device rd;  //Will be used to obtain a seed for the random number engine
					std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
					std::uniform_real_distribution<float> dis(0.0, 1.0);

					//Direct lighting:
					for (std::list<Mesh*>::const_iterator lights = lightList.cbegin(); lights != lightList.cend(); lights++)
					{
						//*****move******
						const std::list<Triangle*> tlist = (*lights)->getTriangleList();
						Material emission_mat = (*lights)->getMaterial();
						for (int j = 0; j < SHADOW_RAY_COUNT; j++)
						{
							for (std::list<Triangle*>::const_iterator t = tlist.cbegin(); t != tlist.cend(); t++)
							{
								
								//Triangle* t = tlist.front() + i;
								float A = (*t)->calculateArea();
								//LOG("area: " << A << "\n")
								float pdf = 1 / A;
								float u = dis(gen);
								float v = dis(gen);
								Vec4 q = (*t)->pickRandomPoint(u, v);

								Vec4 lightDir = q - hitPoint;
								Ray shadow_ray{ hitPoint, lightDir.normalize() };

								float BRDF = lightDir.normalize().dotProduct(norm_hit);

								float lightDistance = lightDir.dotProduct(lightDir);

								Object* shadowObject = nullptr;
								float t_shadow = INFINITY_FLOAT;
								//check normal of object compared with shadowray direction and rule out if its impossible to hit.
								if (BRDF > EPSILON)
								{
									//if object is not in shadow -> calculate radiance from the point.
									if (!(objectIntersect(objectList, shadow_ray, shadowObject, t_shadow) && t_shadow * t_shadow < lightDistance))
									{
										Vec4 Sk = q - hitPoint;
										float dk = Sk.euclideanDist();
										Vec4 Na = (*t)->getNormal();
										Vec4 Nx = norm_hit;
										float alpha = -Sk.dotProduct(Na) / dk;
										float beta = Sk.dotProduct(Nx) / dk;
										radiance += emission_mat.intensity * BRDF * ((alpha * beta) / (dk*dk)) * A / pdf; //no Vk 

									}
								}
							}
						}
					}
					radiance = radiance / SHADOW_RAY_COUNT;

					//Monte Carlo things: (INDIRECT LIGHT)
					
					#ifdef INDIRECT
					//local coordinate system directions for hitpoint:
					Vec4 Y;
					if (fabs(norm_hit.coords[0] > fabs(norm_hit.coords[1])))
					{
						Y = Vec4(norm_hit.coords[2], 0.0f, -norm_hit.coords[0]).normalize();
					}
					else
					{
						Y = Vec4(0.0, -norm_hit.coords[2], norm_hit.coords[1]).normalize();
					}
					Vec4 X = norm_hit.crossProduct(X);
					Vec4 Z = norm_hit;

					const float PDF = 1 / (2.0f * static_cast<float>(M_PI));

					const int N = 10;
					for (unsigned int i = 0; i < N; i++)
					{
						float u = dis(gen);
						float v = dis(gen);
						float r_phi = u * 2.0f * static_cast<float>(M_PI);
						float r_theta = acosf(sqrtf(v));
						//float r_theta = acosf(1 - 2 * v);


						Vec4 randHemiDir = { sinf(r_phi) * sinf(r_theta), sinf(r_phi) * cosf(r_theta), sinf(r_theta) };

						//transform to world coords
						float x = randHemiDir.coords[0] * X.coords[0] + randHemiDir.coords[1] * Y.coords[0] + randHemiDir.coords[2] * Z.coords[0];
						float y = randHemiDir.coords[0] * X.coords[1] + randHemiDir.coords[1] * Y.coords[1] + randHemiDir.coords[2] * Z.coords[1];
						float z = randHemiDir.coords[0] * X.coords[2] + randHemiDir.coords[1] * Y.coords[2] + randHemiDir.coords[2] * Z.coords[2];

						//trace path
						Vec4 M = { x,y,z,1 };
						//M.printCoords();
						Ray indirect_ray = { hitPoint, M };
						//M.printCoords();
						indirect_col = indirect_col + ((tracePath(objectList, lightList, indirect_ray, depth +1) / PDF) * u);
						//indirect_col.printCoords();
					}
					indirect_col = indirect_col / N;
					#endif // DEBUG
					//LOG("radiance: "<< radiance << std::endl)
					col = (hitColor * radiance) +indirect_col;
					//col.printCoords();
					//col = indirect_col;
					break;

				}
				case(MaterialType::EMISSION):
				{
					//LOG("hit light \n")
					col = ColorDbl(255, 255, 255);
					break;
				}
			break;
			}

		}
	}
	return col;
}
void Camera::createImage(const std::string &filename,const std::string &colorSpace)
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
				glm::vec3 rgb = pixel_array[i][j].getColorVec();
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
				glm::vec3 rgb = pixel_array[i][j].getColorVec();
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
				glm::vec3 rgb = pixel_array[i][j].getColorVec();
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
	img.close();


}
void Camera::openImage(std::string filename)
{
	//open the image in a window, how??
}