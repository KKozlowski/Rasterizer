#include "Float4.h"
#include <sstream>
#include "float3.h"
#include "mat4.h"

Float4::Float4(__m128 vector) : m(vector)
{
}

Float4::Float4(float3 vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = 1;
}

Float4::Float4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

Float4::Float4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Float4 Float4::operator+(const Float4& other)
{
	return Float4(_mm_add_ps(m, other.m));
}

Float4 Float4::operator+=(const Float4& other)
{
	m = _mm_add_ps(m, other.m);
	return *this;
}

Float4 Float4::operator-(const Float4& other)
{
	return Float4(_mm_sub_ps(m, other.m));
}

Float4 Float4::operator*(const float& v) const
{
	return Float4(_mm_mul_ps(m, _mm_set1_ps(v)));
}

Float4 Float4::operator*=(float a)
{
	m = _mm_mul_ps(m, _mm_set1_ps(a));
	return (*this);
}

Float4 Float4::operator/(const float& v) const
{
	return Float4(_mm_div_ps(m, _mm_set1_ps(v)));
}

Float4 Float4::operator/=(float a)
{
	m = _mm_div_ps(m, _mm_set1_ps(a));
	return (*this);
}

Float4 Float4::operator-()
{
	return Float4(-x, -y, -z, -w);
}

Float4 Float4::operator*=(Mat4x4 & matrix)
{
	Float4 u(*this);

	x = matrix[0].Dot(u);
	y = matrix[1].Dot(u);
	z = matrix[2].Dot(u);
	w = matrix[3].Dot(u);

	return *this;
}

Float4 Float4::operator*(Mat4x4& matrix)
{
	Float4 u(*this);

	u.x = matrix[0].Dot(*this);
	u.y = matrix[1].Dot(*this);
	u.z = matrix[2].Dot(*this);
	u.w = matrix[3].Dot(*this);

	return u;
}

float Float4::Dot(const Float4& other)
{
	return Float4(_mm_dp_ps(m, other.m, 0xF1)).x;
}

float Float4::Dot3(const Float4& other)
{
	return Float4(_mm_dp_ps(m, other.m, 0x71)).x;
}

Float4 Float4::Cross(const Float4& other)
{
	return _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(other.m, other.m, _MM_SHUFFLE(3, 1, 0, 2))),
		_mm_mul_ps(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(other.m, other.m, _MM_SHUFFLE(3, 0, 2, 1)))
	);
}

Float4 Float4::Multiply(const Float4& other)
{
	return _mm_mul_ps(m, other.m);
}

float Float4::Magnitude()
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m, m, 0x71)));
}

Float4 Float4::GetNormalized()
{
	float mag = Magnitude();
	if (mag < 0.001f)
	{
		return Float4(0, 0, 0, 0);
	}

	return (*this) / mag;
}

void Float4::NormalizeThis()
{
	m = _mm_div_ps(m, _mm_set1_ps(Magnitude()));
}

std::string Float4::ToString()
{
	std::stringstream o;
	o << "{ " << x << ", " << y << ", " << z << ", " << w << " }";
	return o.str();
}
