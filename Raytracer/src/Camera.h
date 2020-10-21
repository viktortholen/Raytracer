#pragma once
#include "Includer.h"
#include "Scene.h"
#include "Pixel.h"
#include "Ray.h"
#include "Object.h"
#include "Light.h"
#define LOG(x) std::cout << x;

static std::mutex sample_mutex;

class Camera {
public:
	Camera();
	~Camera();

	void render(const Scene& scene);
	void createImage(const std::string &filename, const std::string &colorSpace);
	void openImage(std::string filename);
	void renderSample(std::list<Object*>* objectList, std::list<Mesh*>* lightList, Ray* ray, int samples, int i, int j);
	ColorDbl tracePath(std::list<Object*> &objectList, std::list<Mesh*> &lightList, Ray& ray);
	
	bool objectIntersect(std::list<Object*>& objectList, Ray& ray, Object*& hitObject, float& t_closest);
private:
	const int width = 800;
	const int height = 800;
	const float EPSILON = 0.00001f;
	const float INFINITY_FLOAT = std::numeric_limits<float>::max();

	Pixel** pixel_array;
	const Vec4 e1{ -1,0,0 };
	const Vec4 e2{ -2,0,0 };
	bool eyePoint = 0;
	std::vector<std::future<void>> future_vec;
};