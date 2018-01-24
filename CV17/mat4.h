#pragma once
#include "Float4.h"

struct Mat4x4 {
	Float4 mat[4];

	static Mat4x4 identity() {
		static Mat4x4 s = { { { 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 } } }; 
		return s;
	}

	static Mat4x4 zeros()
	{
		static Mat4x4 s = { { { 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } }; 
		return s;
	}

	Mat4x4 operator*(Mat4x4 N);
	Mat4x4 Transposed();
	void TransposeThis();
	Mat4x4 Inversed();

	Float4& operator[] (const int x) {
		return mat[x];
	}
};
