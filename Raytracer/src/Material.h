#pragma once
enum class MaterialType
{
	DIFFUSE_LAMBERTIAN, REFLECTIVE_LAMBERTIAN, EMISSION
};
struct Material {
	//Lambertian properties i dont know...

	Material(const MaterialType& _type, const ColorDbl& col, const float& a) 
		:type{ _type }, diff_col{ col }, absorption{a}{}
	Material()
	{
		type = MaterialType::DIFFUSE_LAMBERTIAN;
		diff_col = ColorDbl(0, 0, 0);
	}

	MaterialType type;
	//int Kd;//?
	//float Ks;
	ColorDbl diff_col;
	//ColorDbl BRDF;
	float absorption = 0.9f;
	float intensity = 10.0f;
};