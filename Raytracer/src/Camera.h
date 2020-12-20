#pragma once
#include "Includer.h"
#include "Scene.h"
#include "Pixel.h"
#include "Ray.h"
#include "Object.h"
#include "Light.h"
#define LOG(x) std::cout << x;



class Camera {
public:
	
	Camera();
	~Camera();

	void render(const Scene& scene);
	void createImage(const std::string &filename, const std::string &colorSpace);
	ColorDbl tracePath(const std::vector<std::shared_ptr<Object>>& objectList, const std::vector<std::shared_ptr<Mesh>>& lightList, Ray& ray, const int& depth);
	
	bool objectIntersect(const std::vector<std::shared_ptr<Object>>& objectList, Ray& ray, std::shared_ptr<Object>& hitObject, float& t_closest) const;
	void setEyePoint(const Vec4& eyePoint);
private:
	const int width = 800;
	const int height = 800;
	const float EPSILON = 0.00001f;
	const float INFINITY_FLOAT = std::numeric_limits<float>::max();

	Pixel** pixel_array;
	Vec4 e{ -1,0,0 };
	std::vector<std::future<ColorDbl>> future_vec;
	int max_depth = 0;

	const int SHADOW_RAY_COUNT = 1;
	const int samples = 16;
	const float gamma = 1.0f;
	const float direct_contribution = 1.0f * gamma;
	const float indirect_contribution = 0.5f * gamma;

	//test shadow rays, samples, ray-depth, 

};