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
	void createImage(std::string filename, std::string colorSpace);
	void openImage(std::string filename);
	ColorDbl tracePath(std::list<Object*> &objectList, std::list<Light*> &lightList, Ray& ray, int depth);
	bool objectIntersect(std::list<Object*>& objectList, Ray& ray, Object*& hitObject, float& t_closest);
	Vec4 calcRandomHemiDir(const float& r_phi, const float& r_theta);
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