#pragma once
#include "Float4.h"

struct Color {
	Float4 argb;

	Color() : argb(Float4(0, 0, 0, 0)){}
	Color(__m128 _argb) : argb(Float4(_argb)) {}
	Color(float _a, float _r, float _g, float _b) : argb(Float4(_a,_r,_g,_b)){}
	Color(Float4 f) : argb(f){}

	Color operator*(Color value);
	Color operator*(float multiplier);
	Color operator*(Float4 v);
	Color operator=(Color value);
	Color operator=(Float4 argb);
	Color operator+(Color value);

	float A() { return argb[0]; }
	float R() { return argb[1]; }
	float G() { return argb[2]; }
	float B() { return argb[3]; }

	uint8_t i_A() { return (uint8_t)(argb[0]*255); }
	uint8_t i_R() { return (uint8_t)(argb[1] * 255); }
	uint8_t i_G() { return (uint8_t)(argb[2] * 255); }
	uint8_t i_B() { return (uint8_t)(argb[3] * 255); }

	unsigned int ToUInt32() { return i_B() + (i_G() << 8) + (i_R() << 16) + (i_A() << 24); }

	static Color GetRandom();

	std::string ToString();
};
