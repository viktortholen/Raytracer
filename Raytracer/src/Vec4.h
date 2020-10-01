#pragma once

//#include "Triangle.h"
class Vec4 {
public:
	Vec4() = default;
	Vec4(float x, float y, float z, float w = 1)
		:coords{x, y, z, w } {}
	~Vec4() = default;

	Vec4(const Vec4& other) {
		coords = other.coords;

	}

	Vec4& operator=(Vec4 p) { //assignment
		Vec4 temp{ p };
		std::swap(p.coords, coords);
		return *this;
	}

	Vec4 operator-(const Vec4& v) const{
		Vec4 tmp{ *this };
		tmp.coords[0] -= v.coords[0];
		tmp.coords[1] -= v.coords[1];
		tmp.coords[2] -= v.coords[2];
		return tmp;
	}	
	Vec4 operator-(const float& v) const {
		Vec4 tmp{ *this };
		tmp.coords[0] -= v;
		tmp.coords[1] -= v;
		tmp.coords[2] -= v;
		return tmp;
	}
	Vec4 operator+(const Vec4& v) const {
		Vec4 tmp{ *this };
		tmp.coords[0] += v.coords[0];
		tmp.coords[1] += v.coords[1];
		tmp.coords[2] += v.coords[2];
		return tmp;
	}
	Vec4 operator*(const float& f)
	{
		coords[0] *= f;
		coords[1] *= f;
		coords[2] *= f;
		return *this;
	}
	//Vec3f operator * (const float& r) const { return Vec3f(x * r, y * r, z * r); }
	//Vec3f operator * (const Vec3f& v) const { return Vec3f(x * v.x, y * v.y, z * v.z); }
	//Vec3f operator - (const Vec3f& v) const { return Vec3f(x - v.x, y - v.y, z - v.z); }
	//Vec3f operator + (const Vec3f& v) const { return Vec3f(x + v.x, y + v.y, z + v.z); }
	//Vec3f operator - () const { return Vec3f(-x, -y, -z); }
	//Vec3f& operator += (const Vec3f& v) { x += v.x, y += v.y, z += v.z; return *this; }

	friend Vec4 operator* (const float& r, const Vec4& v)
	{
		return Vec4(v.coords[0] * r, v.coords[1] * r, v.coords[2] * r, v.coords[3]);
	}
	friend Vec4 operator- (const float& r, const Vec4& v)
	{
		return Vec4(v.coords[0] - r, v.coords[1] - r, v.coords[2] - r, v.coords[3]);
	}
	//friend Vec4 operator+ (const Vec4& v1, const Vec4& v2)
	//{
	//	return Vec4(v1.coords[0] + v2.coords[0], v1.coords[1] + v2.coords[1], v1.coords[2] + v2.coords[2], v1.coords[3] + v2.coords[3]);
	//}


	Vec4 crossProduct(const Vec4& v) const
	{
		glm::vec3 res = glm::cross(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
		return Vec4(res[0], res[1], res[2], 1);
	}
	float dotProduct(const Vec4& v) const
	{
		return glm::dot(glm::vec3(coords[0], coords[1], coords[2]), glm::vec3(v.coords[0], v.coords[1], v.coords[2]));
	}
	void printCoords()
	{
		std::cout << "\nx: " << coords[0] << ", y: " << coords[1] << " , z: " << coords[2];
	}
	
	Vec4 normalize()
	{
		glm::vec3 tmp = {coords[0],coords[1] ,coords[2]};
		tmp = glm::normalize(tmp);
		return Vec4{ tmp[0], tmp[1] ,tmp[2], coords[3]};
	}
	Vec4 reflect(const Vec4& N) //direction and normal
	{
		Vec4 dir{*this};
		return dir - 2 * dir.dotProduct(N) * N;
	}

private:
	glm::vec4 coords;
	friend class Triangle;
	friend class Scene;

};