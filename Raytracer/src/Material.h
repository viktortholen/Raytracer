#pragma once
enum MaterialType
{
	DIFFUSE, REFLECTIVE
};
struct Material {
	//Lambertian properties i dont know...

	Material(MaterialType _type, ColorDbl col) 
		:type{ _type }, diff_col{ col }{}
	Material()
	{
		type = MaterialType::DIFFUSE;
		diff_col = ColorDbl(0, 0, 0);
	}

	MaterialType type;
	int Kd;//?
	ColorDbl diff_col;

};