#include "float3.h"

float3::float3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

float3::float3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float3::float3(double x, double y) : float3(x, y, 0){}

void float3::Normalize()
{
	double Magnitude = this->Magnitude();
	if (Magnitude == 0) throw "Zero vector cannot be normalized";

	x /= Magnitude;
	y /= Magnitude;
	z /= Magnitude;
}

float3 float3::GetNormalized() const
{
	double Magnitude = this->Magnitude();
	if (Magnitude == 0) throw "Zero vector cannot be normalized";

	return float3(x / Magnitude, y / Magnitude, z / Magnitude);
}

double float3::MagnitudeSquared() const
{
	return x * x + y * y + z * z;
}

double float3::Magnitude() const
{
	return (sqrt(MagnitudeSquared()));
}

float3 float3::operator/(const double& v) const
{
	return float3(x / v, y / v, z / v);
}

float3 float3::operator/(const float3& v) const
{
	return float3(x / v.x, y / v.y, z / v.z);
}

float3 float3::operator*(const double& v) const
{
	return float3(x * v, y * v, z * v);
}

float3 float3::operator*(const float3& v) const
{
	return float3(x * v.x, y * v.y, z * v.z);
}

float3 float3::operator+(const float3& v) const
{
	return float3(x + v.x, y + v.y, z + v.z);
}

float3 float3::operator-(const float3& v) const
{
	return float3(x - v.x, y - v.y, z - v.z);
}

float3 float3::operator-() const
{
	return float3(-x, -y, -z);
}

void float3::operator+=(const float3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void float3::operator-=(const float3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

float3 float3::Cross(float3 vec) const
{
	return float3(
		((y * vec.z) - (z * vec.y)),
		((z * vec.x) - (x * vec.z)),
		((x * vec.y) - (y * vec.x))
	);
}

float3* float3::Clone() const
{
	return new float3(x, y, z);
}

double float3::Dot(float3 vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

float3 float3::Reflect(float3 normal) const
{
	return *this - (normal * 2 * this->Dot(normal));
}

float3 float3::Cross(float3 one, float3 two)
{
	return one.Cross(two);
}

std::string float3::ToString() const
{
	std::ostringstream ss;
	ss << "float3 { " << x << ", " << y << ", " << z << " }";
	return ss.str();
}

float3 float3::Lerp(float3 v, double t) const
{
	return float3(
		x + t * (v.x - x),
		y + t * (v.y - y),
		z + t * (v.z - z)
		);
}

float3 const float3::zero = float3(0, 0, 0);
float3 const float3::one = float3(1, 1, 1);