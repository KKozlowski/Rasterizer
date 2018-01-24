#pragma once
#include <cmath>
#include <iostream>
#include <sstream>

///<summary>
///Przechowuje informacje o punkcie w trójwymiarowym ukladzie odniesienia.
///</summary>
class float3
{
public:
	float3();

	float3(double x, double y, double z);

	float3(double x, double y);

	double x, y, z;
	void Normalize();

	float3 GetNormalized() const;

	double MagnitudeSquared() const;

	double Magnitude() const;

	float3 operator /(const double& v) const;

	float3 operator /(const float3& v) const;

	float3 operator *(const double& v) const;

	float3 operator *(const float3& v) const;

	float3 operator +(const float3& v) const;

	float3 operator -(const float3& v) const;

	float3 operator-() const;

	void operator+=(const float3& v);

	void operator-=(const float3& v);

	bool operator==(const float3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

	bool operator!=(const float3& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

	float3 Cross(float3 vec) const;

	float3 *Clone() const;

	double Dot(float3 vec) const;

	float3 Reflect(float3 normal) const;

	static float3 Cross(float3 one, float3 two);

	std::string ToString() const;

	float3 Lerp(float3 v, double t) const;

	static float3 const zero;
	static float3 const one;
};