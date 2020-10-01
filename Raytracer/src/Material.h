#pragma once
enum class MaterialType
{
	DIFFUSE_LAMBERTIAN, REFLECTIVE_LAMBERTIAN
};
struct Material {
	//Lambertian properties i dont know...

	Material(MaterialType _type, ColorDbl col) 
		:type{ _type }, diff_col{ col }{}
	Material()
	{
		type = MaterialType::DIFFUSE_LAMBERTIAN;
		diff_col = ColorDbl(0, 0, 0);
	}

	MaterialType type;
	int Kd;//?
	float Ks;
	ColorDbl diff_col;
	ColorDbl BRDF;
	float reflectance;
};