#pragma once
enum class MaterialType
{
	DIFFUSE_LAMBERTIAN, REFLECTION, EMISSION, REFRACTION
};
struct Material {

	Material(const MaterialType& _type, const ColorDbl& col, const float& a, const float& r, const float& _IOR)
		:type{ _type }, diff_col{ col }, absorption{ a }, reflectance{ r }, IOR{_IOR}{}
	Material()
	{
		type = MaterialType::DIFFUSE_LAMBERTIAN;
		diff_col = ColorDbl(0, 0, 0);
	}

	MaterialType type;
	ColorDbl diff_col;
	float absorption = 0.9f;
	float intensity = 1.0f;
	float reflectance;
	float IOR;
};