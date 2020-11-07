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
void Camera::setEyePoint(const Vec4& eyePoint) {
	e = eyePoint;
}
void Camera::render(const Scene& scene) {

	//define options:
	#define INDIRECT
	#define MULTI_THREADING
	#define LOGGING
	int samples = 10;
	//*****************
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();

	//for loop för att gå igenom pixlar - skjuta Ray genom alla
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
			LOG("\r Initializing: " << percentage << std::fixed << std::setprecision(5) << std::left << std::setw(7) << "%");
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
							Vec4 dir = pixelIntersection - e;
							Ray ray{ e, dir.normalize() };
							col = col + tracePath(objectList, lightList, ray, 0);
						}
						col = col / static_cast<float>(samples);
						//col.printCoords();
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
				Vec4 dir = pixelIntersection - e;
				Ray ray{ e, dir.normalize() };
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
	std::cout<<"-Starting rendering-\n Time: " << duration.count() << "s";
#ifdef MULTI_THREADING
	std::cout << "\n Rendering...\n";

	auto wait_start = std::chrono::high_resolution_clock::now();
	int size = future_vec.size();
	for (unsigned int i = 0; i < future_vec.size(); i++)
	{
		if (i % 1000 == 0)
		{
			std::cout << "\rPixels done: " <<i << " / "<< size << std::fixed << std::setprecision(5) << std::left << std::setw(7);
		}
		future_vec[i].wait();

	}
	auto wait_end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration2 = wait_end - wait_start;
	std::cout << "-Finished waiting-\n Time: " << duration2.count() << "s";
	std::cout << "\n-Total time: " << duration.count() + duration2.count() << "s";
	std::cout << "\n-Total diffuse bounces: " << max_depth;

#endif
	std::cout << "\n******************************\n";


}
bool Camera::objectIntersect(const std::vector<std::shared_ptr<Object>> &objectList, 
	Ray& ray, std::shared_ptr<Object>& hitObject, float& t_closest) const
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
ColorDbl Camera::tracePath(const std::vector<std::shared_ptr<Object>> &objectList, 
	const std::vector<std::shared_ptr<Mesh>>& lightList, 
	Ray& ray, const int& depth)
{
	if (depth > max_depth)
	{
		max_depth = depth;
		//LOG("max_depth: " <<max_depth<<"\n")
	}

	ColorDbl col;
	std::shared_ptr<Object> hitObject = nullptr;

	//options: *************************
	float t_temp = INFINITY_FLOAT;
	const int SHADOW_RAY_COUNT = 2;
	int N = 1;
	const float gamma = 1.0f;
	const float direct_contribution = 1.0f * gamma;
	const float indirect_contribution = 0.5f * gamma;
	//***********************************
	if (objectIntersect(objectList, ray, hitObject, t_temp))
	{
		Material hitMat = hitObject->getMaterial();
		ColorDbl hitColor = ray.getColor();
		Vec4 dir = ray.getDirection().normalize();
		Vec4 hit_normal = ray.getHitNormal().normalize();

		Vec4 hitPoint = ray.getOffsetEndPointAlongNormal(EPSILON);

		switch (hitMat.type)
		{
			case(MaterialType::REFLECTION): //perfect mirror
			{

				Vec4 refl_dir = dir.reflect(hit_normal).normalize(); //perfect reflection
				//trace new ray in the reflection direction:
				Ray refl_ray{ hitPoint, refl_dir };

				col = tracePath(objectList, lightList, refl_ray, depth);
				break;
			}
			case(MaterialType::REFRACTION): //perfect mirror
			{
				float n1 = 1.0;
				float n2 = hitMat.IOR;
				
				float cost = hit_normal.dotProduct(dir * -1);

				Vec4 N = hit_normal;
				if(cost < 0)
				{
					cost = -cost;
				}else
				{
					std::swap(n1, n2);

					N = hit_normal * -1;
				}


				Vec4 R = dir.reflect(N).normalize(); //perfect reflection
				Vec4 T = dir.refract(N, n1 , n2).normalize(); //refraction
				//trace new ray in the reflection direction:
				Ray refl_ray{ hitPoint, R };
				Ray refr_ray{ hitPoint, T };

				ColorDbl refl_col = tracePath(objectList, lightList, refl_ray, depth);
				ColorDbl refr_col = tracePath(objectList, lightList, refr_ray, depth);


				/*float Rs = pow((n1 * cost - n2 * sqrt(1 - pow((n1 / n2) * sinf(acosf(cost)), 2)))
							/ (n1 * cost + n2 * sqrt(1 - pow((n1 / n2) * sinf(acosf(cost)), 2))), 2);
				
				float Rp = pow((n1 * sqrt(1 - pow((n1 / n2) * sinf(acosf(cost)), 2)) - n2*cost)
							/  (n1 * sqrt(1 - pow((n1 / n2) * sinf(acosf(cost)), 2)) + n2 * cost), 2);

				float refl_coeff = (Rs + Rp) / 2;*/

				float R0 = pow((n1 - n2) / (n1 + n2), 2);

				float refl_coeff = R0 + (1 - R0) * pow((1 - cos(acos(cost))), 5);

				col = (refl_col * refl_coeff) + (refr_col * (1 - refl_coeff));
				//col = (refr_col * (1 - refl_coeff));
				//col = tracePath(objectList, lightList, refl_ray, depth);
				break;
			}
			case(MaterialType::DIFFUSE_LAMBERTIAN): //
			{
				std::random_device rd;  //Will be used to obtain a seed for the random number engine
				std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
				std::uniform_real_distribution<float> dis(0.0, 1.0);
				float P = dis(gen);


				float radiance = 0.0f;
			

				//Direct lighting:
				for (const auto light: lightList)
				{

					//TODO: check if light normal is in the same direction as hitnormal!
					const auto tlist = light->getTriangleList();
					Material emission_mat = light->getMaterial();
					for (int j = 0; j < SHADOW_RAY_COUNT; j++)
					{
						for (const auto t: tlist)
						{
								
							//Triangle* t = tlist.front() + i;
							float A = t->calculateArea();
							//LOG("area: " << A << "\n")
							float PDF = 1 / A;
							float u = dis(gen);
							float v = dis(gen);
							Vec4 q = t->pickRandomPoint(u, v);

							Vec4 lightDir = q - hitPoint;
							Ray shadow_ray{ hitPoint, lightDir.normalize() };

							float BRDF = lightDir.normalize().dotProduct(hit_normal);
							//float BRDF = hitMat.reflectance / M_PI;

							float lightDistance = lightDir.dotProduct(lightDir);

							std::shared_ptr<Object> shadowObject = nullptr;
							float t_shadow = INFINITY_FLOAT;
							//check normal of object compared with shadowray direction and rule out if its impossible to hit.
							if (BRDF > EPSILON)
							{
								//if object is not in shadow -> calculate radiance from the point.
								if (!(objectIntersect(objectList, shadow_ray, shadowObject, t_shadow) && 
									t_shadow * t_shadow < lightDistance))
								{
									Vec4 Sk = q - hitPoint;
									float dk = Sk.euclideanDist();
									Vec4 Na =t->getNormal();
									Vec4 Nx = hit_normal;
									float alpha = -Sk.dotProduct(Na) / dk;
									float beta = Sk.dotProduct(Nx) / dk;
									radiance += emission_mat.intensity * BRDF * ((alpha * beta) / (dk * dk));// *A / PDF; //no Vk 
								}
							}
						}
					}
				}
				radiance = radiance / SHADOW_RAY_COUNT;
				ColorDbl directColor = hitColor * radiance;
				ColorDbl indirect_col; //irradiance
				//Monte Carlo things: (INDIRECT LIGHT)
				#ifdef INDIRECT

				if (P > 1 - hitMat.absorption && depth > 1)
					return directColor;

				
				//local coordinate system directions for hitpoint:
				//Vec4 Y;
				//if (fabs(hit_normal.coords[0] > fabs(hit_normal.coords[1])))
				//{
				//	Y = Vec4(hit_normal.coords[2], 0.0f, -hit_normal.coords[0]).normalize();
				//}
				//else
				//{
				//	Y = Vec4(0.0, -hit_normal.coords[2], hit_normal.coords[1]).normalize();
				//}
				//Vec4 X = hit_normal.crossProduct(X);
				//Vec4 Z = hit_normal;

				Vec4 X = (dir - (dir.dotProduct(hit_normal) * hit_normal)).normalize();
				Vec4 Z = hit_normal;
				Vec4 X_neg = X * -1.0f;
				Vec4 Y = X_neg.crossProduct(Z);

				
				//Vec4 v1 = dir - (dir.dotProduct(hit_normal) * hit_normal).normalize();
				//Vec4 v3 = hit_normal;
				//Vec4 v2 = -v1.crossProduct(v3);

				
				const float PDF = 1 / (2.0f * static_cast<float>(M_PI));
				for (int i = 0; i < N; i++)
				{
					float u = dis(gen);
					float v = dis(gen);
					
					if ((2.0f * static_cast<float>(M_PI)) / P * u > 2.0f * static_cast<float>(M_PI) && depth > 1)
					{
						N = i+1;
						break;
					}
					

					float r_phi = u * 2.0f * static_cast<float>(M_PI);
					float r_theta = asinf(sqrtf(v));
					Vec4 randHemiDir = { cosf(r_phi) * sinf(r_theta), sinf(r_phi) * sinf(r_theta), cosf(r_theta) };
					/*std::cout << r_phi << " " << r_theta << "\n";*/
					//float BRDF = hitMat.reflectance / M_PI;
					//float r_theta = sqrtf(u);
					//float r_phi = 2.0f * static_cast<float>(M_PI) * v;
					//Vec4 randHemiDir = { r_theta * cosf(r_phi) ,u, r_theta * sinf(r_phi) };

					//transform to world coords
					float x = randHemiDir.coords[0] * X.coords[0] + randHemiDir.coords[1] *Y.coords[0] + randHemiDir.coords[2] *Z.coords[0];
					float y = randHemiDir.coords[0] * X.coords[1] + randHemiDir.coords[1] *Y.coords[1] + randHemiDir.coords[2] *Z.coords[1];
					float z = randHemiDir.coords[0] * X.coords[2] + randHemiDir.coords[1] *Y.coords[2] + randHemiDir.coords[2] *Z.coords[2];

					//trace path
					Vec4 M = { x,y,z,1 };
					//M.printCoords();
					Ray indirect_ray = { hitPoint, M };
					//M.printCoords();
					indirect_col = indirect_col + (tracePath(objectList, lightList, indirect_ray, depth+1));
					//indirect_col.printCoords();
				}
				
				//indirect_col.printCoords();
				//std::cout << std::endl;
				indirect_col = indirect_col / N;
				#endif // DEBUG
				
				ColorDbl normalize(255, 255, 255);
				col = ((normalize * radiance * direct_contribution) + (indirect_col * indirect_contribution)) * hitColor / normalize;
				break;

			}
			case(MaterialType::EMISSION):
			{
				return ColorDbl(255, 255, 255)* hitMat.intensity;

			}
			default:
			{
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