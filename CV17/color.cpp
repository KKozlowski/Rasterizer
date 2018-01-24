#include "Color.h"
#include <algorithm>
#include <sstream>

Color Color::operator*(Color value)
{
	return argb.Multiply(value.argb);
}

Color Color::operator*(float multiplier)
{
	return  _mm_min_ps(_mm_max_ps((argb*multiplier).m, _mm_set1_ps(0)), _mm_set1_ps(1));
}

Color Color::operator*(Float4 v)
{
	return  _mm_min_ps(_mm_max_ps((argb.Multiply(v)).m, _mm_set1_ps(0)), _mm_set1_ps(1)) ;
}

Color Color::operator=(Color value)
{
	this->argb = value.argb;
	return *this;
}

Color Color::operator=(Float4 argb)
{
	this->argb = argb;
	return *this;
}

Color Color::operator+(Color value)
{
	return  _mm_min_ps((argb + value.argb).m, _mm_set1_ps(1));
}

unsigned int uiRand(int min, int max)
{
	return min + rand() % (max - min);
}

float fRand(float min, float max)
{
	return min + ((rand() % 1000)*0.001f) * (max - min);
}

Color Color::GetRandom()
{
	return Color(1, fRand(0.4f,1), fRand(0.4f, 1), fRand(0.4f, 1));
}

std::string Color::ToString()
{
	std::stringstream o;
	o << "{ " << A() << ", " << R() << ", " << G() << ", " << B() << " }";
	return o.str();
}
