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

	//define options:
	//#define INDIRECT
	#define MULTI_THREADING
	#define LOGGING
	int samples = 10;
	//*****************

	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();

	//for loop f�r att g� igenom pixlar - skjuta Ray genom alla
	int quad_size_y = (width / 2) + 1;
	int quad_size_z = (height / 2) + 1;
	float delta = static_cast<float>(2.0 / width);

	float percentage;
	
	const auto objectList = scene.getObjectList();
	const auto lightList = scene.getLightList();

	std::condition_variable cvResults;
	for (int i = 0; i < width; i++)
	{
		#ifdef LOGGING
			//LOG progress:
			percentage = (static_cast<float>((i + 1)) / width) * 100;
			LOG("\rRendering: " << percentage << std::fixed << std::setprecision(5) << std::left << std::setw(7) << "%");
			/******************************************/
		#endif

		for (int j = 0; j < height; j++)
		{

			#ifdef MULTI_THREADING
			future_vec.emplace_back(std::async(std::launch::async,
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

					}));

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
#ifdef MULTI_THREADING
	std::cout << "\nFinishing...\n";

	auto wait_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < future_vec.size(); i++)
	{
		future_vec[i].wait();

	}
	auto wait_end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration2 = wait_end - wait_start;
	std::cout << "-Finished waiting-\n Time: " << duration2.count() << "s";
	std::cout << "\n-Total time: " << duration.count() + duration2.count() << "s";

#endif
	std::cout << "\n******************************\n";


}

//ColorDbl Camera::renderSample(const std::vector<Object*>* objectList, const std::vector<Mesh*>* lightList, Ray* ray, int samples, volatile std::atomic<std::size_t>* at_i, volatile std::atomic<std::size_t>* at_j)
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
bool Camera::objectIntersect(const std::vector<std::shared_ptr<Object>> &objectList, Ray& ray, std::shared_ptr<Object>& hitObject, float& t_closest) const
{
	//std::lock_guard<std::mutex> lock(sample_mutex);
		hitObject = nullptr;
		float obj_closest = INFINITY_FLOAT;

		for (auto object: objectList)
		{
			if (object->castRay(ray, t_closest) && t_closest < obj_closest) //object is hit
			{
				hitObject = object;
				obj_closest = t_closest;
			}

		}

		if (hitObject == nullptr)
			return false;

		
	
	return true;
}
ColorDbl Camera::tracePath(const std::vector<std::shared_ptr<Object>> &objectList, const std::vector<std::shared_ptr<Mesh>>& lightList, Ray& ray, const int& depth)
{
	//LOG("depth: " <<depth<<"\n")
	ColorDbl col;
	std::shared_ptr<Object> hitObject = nullptr;
	//loop through objects instead of meshes (includes spheres)
	float t_temp = INFINITY_FLOAT;
	const int SHADOW_RAY_COUNT = 5;
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
					for (const auto light: lightList)
					{

						//*****move******
						const auto tlist = light->getTriangleList();
						Material emission_mat = light->getMaterial();
						for (int j = 0; j < SHADOW_RAY_COUNT; j++)
						{
							for (const auto t: tlist)
							{
								
								//Triangle* t = tlist.front() + i;
								float A = t->calculateArea();
								//LOG("area: " << A << "\n")
								float pdf = 1 / A;
								float u = dis(gen);
								float v = dis(gen);
								Vec4 q = t->pickRandomPoint(u, v);

								Vec4 lightDir = q - hitPoint;
								Ray shadow_ray{ hitPoint, lightDir.normalize() };

								float BRDF = lightDir.normalize().dotProduct(norm_hit);

								float lightDistance = lightDir.dotProduct(lightDir);

								std::shared_ptr<Object> shadowObject = nullptr;
								float t_shadow = INFINITY_FLOAT;
								//check normal of object compared with shadowray direction and rule out if its impossible to hit.
								if (BRDF > EPSILON)
								{
									//if object is not in shadow -> calculate radiance from the point.
									if (!(objectIntersect(objectList, shadow_ray, shadowObject, t_shadow) && t_shadow * t_shadow < lightDistance)) //causes undefined - objectlist
									{
										Vec4 Sk = q - hitPoint;
										float dk = Sk.euclideanDist();
										Vec4 Na =t->getNormal();
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
					for (int i = 0; i < N; i++)
					{
						//float u = dis(gen);
						//float v = dis(gen);
						//float r_phi = u * 2.0f * static_cast<float>(M_PI);
						//float r_theta = acosf(sqrtf(v));
						////float r_theta = acosf(1 - 2 * v);


						//Vec4 randHemiDir = { sinf(r_phi) * sinf(r_theta), sinf(r_phi) * cosf(r_theta), sinf(r_theta) };
						float u = dis(gen);
						float v = dis(gen);
						float r_theta = sqrtf(1 - u*u);
						float r_phi = 2.0f * static_cast<float>(M_PI)* v;

						Vec4 randHemiDir = { r_theta * cosf(r_phi) ,u, r_theta * sinf(r_phi) };

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
				default:
				{
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