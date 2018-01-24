#pragma once

#include "xmmintrin.h"
#include "smmintrin.h"
#include <string>

struct Mat4x4;
class float3;

union Float4 {
private:
	float f[4];
public:
	struct { float x, y, z, w; };
	__m128 m;

	Float4() {}

	Float4(__m128 vector);

	Float4(float3 vector);

	Float4(float x, float y, float z);

	Float4(float x, float y, float z, float w);

	Float4 operator+(const Float4& other);
	Float4 operator+=(const Float4& other);

	Float4 operator-(const Float4& other);

	Float4 operator *(const float& v) const;
	Float4 operator*=(float a);

	Float4 operator /(const float& v) const;
	Float4 operator/=(float a);

	Float4 operator-();

	Float4 operator*=(Mat4x4 & matrix);
	Float4 operator*(Mat4x4 & matrix);

	float Dot(const Float4& other);
	float Dot3(const Float4& other);

	Float4 Cross(const Float4& other);
	Float4 Multiply(const Float4& other);

	float Magnitude();

	float SquaredMagnitude() { return (x*x) + (y*y) + (z*z); }

	Float4 GetNormalized();
	void NormalizeThis();

	std::string ToString();

	float& operator[] (const int x) {
		return f[x];
	}
};
