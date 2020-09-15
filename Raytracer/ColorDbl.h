#pragma once
#include "Includer.h"

class ColorDbl {
public:
	ColorDbl() = default;
	ColorDbl(double _r, double _g, double _b) 
		:r{ _r }, g{ _g }, b{ _b } {}

private:
	double r, g, b;
};