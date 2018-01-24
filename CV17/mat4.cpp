#include "mat4.h"
# include "xmmintrin.h"

Mat4x4 Mat4x4::operator*(Mat4x4 N)
{
	Mat4x4 M = zeros();

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				M.mat[i][k] += mat[i][j] * N.mat[j][k];
			}
		}
	}

	return M;
}

Mat4x4 Mat4x4::Transposed()
{
	Mat4x4 M = { { { mat[0][0], mat[1][0], mat[2][0], mat[3][0] },
	{ mat[0][1], mat[1][1], mat[2][1], mat[3][1] },
	{ mat[0][2], mat[1][2], mat[2][2], mat[3][2] },
	{ mat[0][3], mat[1][3], mat[2][3], mat[3][3] } } };
	//
	return M;
}

void Mat4x4::TransposeThis()
{
	_MM_TRANSPOSE4_PS(mat[0].m, mat[1].m, mat[2].m, mat[3].m)
}

Mat4x4 Mat4x4::Inversed()
{
	Mat4x4 inv;

	inv.mat[0][0] = mat[1][1] * mat[2][2] * mat[3][3] 
	- mat[1][1] * mat[2][3] * mat[3][2] 
	- mat[2][1] * mat[1][2] * mat[3][3] 
	+ mat[2][1] * mat[1][3] * mat[3][2] 
	+ mat[3][1] * mat[1][2] * mat[2][3] 
	- mat[3][1] * mat[1][3] * mat[2][2];

	inv.mat[1][0] = -mat[1][0] * mat[2][2] * mat[3][3] 
	+ mat[1][0] * mat[2][3] * mat[3][2] 
	+ mat[2][0] * mat[1][2] * mat[3][3] 
	- mat[2][0] * mat[1][3] * mat[3][2] 
	- mat[3][0] * mat[1][2] * mat[2][3] 
	+ mat[3][0] * mat[1][3] * mat[2][2];

	inv.mat[2][0] = mat[1][0] * mat[2][1] * mat[3][3] 
	- mat[1][0] * mat[2][3] * mat[3][1] 
	- mat[2][0] * mat[1][1] * mat[3][3] 
	+ mat[2][0] * mat[1][3] * mat[3][1] 
	+ mat[3][0] * mat[1][1] * mat[2][3] 
	- mat[3][0] * mat[1][3] * mat[2][1];

	inv.mat[3][0] = -mat[1][0] * mat[2][1] * mat[3][2] 
	+ mat[1][0] * mat[2][2] * mat[3][1] 
	+ mat[2][0] * mat[1][1] * mat[3][2] 
	- mat[2][0] * mat[1][2] * mat[3][1] 
	- mat[3][0] * mat[1][1] * mat[2][2] 
	+ mat[3][0] * mat[1][2] * mat[2][1];

	inv.mat[0][1] = -mat[0][1] * mat[2][2] * mat[3][3] 
	+ mat[0][1] * mat[2][3] * mat[3][2]
	+ mat[2][1] * mat[0][2] * mat[3][3] 
	- mat[2][1] * mat[0][3] * mat[3][2] 
	- mat[3][1] * mat[0][2] * mat[2][3] 
	+ mat[3][1] * mat[0][3] * mat[2][2];

	inv.mat[1][1] = mat[0][0] * mat[2][2] * mat[3][3] 
	- mat[0][0] * mat[2][3] * mat[3][2] 
	- mat[2][0] * mat[0][2] * mat[3][3] 
	+ mat[2][0] * mat[0][3] * mat[3][2] 
	+ mat[3][0] * mat[0][2] * mat[2][3] 
	- mat[3][0] * mat[0][3] * mat[2][2];

	inv.mat[2][1] = -mat[0][0] * mat[2][1] * mat[3][3] 
	+ mat[0][0] * mat[2][3] * mat[3][1] 
	+ mat[2][0] * mat[0][1] * mat[3][3] 
	- mat[2][0] * mat[0][3] * mat[3][1] 
	- mat[3][0] * mat[0][1] * mat[2][3] 
	+ mat[3][0] * mat[0][3] * mat[2][1];

	inv.mat[3][1] = mat[0][0] * mat[2][1] * mat[3][2] 
	- mat[0][0] * mat[2][2] * mat[3][1] 
	- mat[2][0] * mat[0][1] * mat[3][2] 
	+ mat[2][0] * mat[0][2] * mat[3][1] 
	+ mat[3][0] * mat[0][1] * mat[2][2] 
	- mat[3][0] * mat[0][2] * mat[2][1];

	inv.mat[0][2] = mat[0][1] * mat[1][2] * mat[3][3] 
	- mat[0][1] * mat[1][3] * mat[3][2] 
	- mat[1][1] * mat[0][2] * mat[3][3] 
	+ mat[1][1] * mat[0][3] * mat[3][2] 
	+ mat[3][1] * mat[0][2] * mat[1][3] 
	- mat[3][1] * mat[0][3] * mat[1][2];

	inv.mat[1][2] = -mat[0][0] * mat[1][2] * mat[3][3] 
	+ mat[0][0] * mat[1][3] * mat[3][2] 
	+ mat[1][0] * mat[0][2] * mat[3][3] 
	- mat[1][0] * mat[0][3] * mat[3][2] 
	- mat[3][0] * mat[0][2] * mat[1][3] 
	+ mat[3][0] * mat[0][3] * mat[1][2];

	inv.mat[2][2] = mat[0][0] * mat[1][1] * mat[3][3] 
	- mat[0][0] * mat[1][3] * mat[3][1] 
	- mat[1][0] * mat[0][1] * mat[3][3] 
	+ mat[1][0] * mat[0][3] * mat[3][1] 
	+ mat[3][0] * mat[0][1] * mat[1][3] 
	- mat[3][0] * mat[0][3] * mat[1][1];

	inv.mat[3][2] = -mat[0][0] * mat[1][1] * mat[3][2] 
	+ mat[0][0] * mat[1][2] * mat[3][1] 
	+ mat[1][0] * mat[0][1] * mat[3][2] 
	- mat[1][0] * mat[0][2] * mat[3][1]
	- mat[3][0] * mat[0][1] * mat[1][2] 
	+ mat[3][0] * mat[0][2] * mat[1][1];

	inv.mat[0][3] = -mat[0][1] * mat[1][2] * mat[2][3] 
	+ mat[0][1] * mat[1][3] * mat[2][2] 
	+ mat[1][1] * mat[0][2] * mat[2][3] 
	- mat[1][1] * mat[0][3] * mat[2][2] 
	- mat[2][1] * mat[0][2] * mat[1][3] 
	+ mat[2][1] * mat[0][3] * mat[1][2];

	inv.mat[1][3] = mat[0][0] * mat[1][2] * mat[2][3] 
	- mat[0][0] * mat[1][3] * mat[2][2] 
	- mat[1][0] * mat[0][2] * mat[2][3] 
	+ mat[1][0] * mat[0][3] * mat[2][2] 
	+ mat[2][0] * mat[0][2] * mat[1][3] 
	- mat[2][0] * mat[0][3] * mat[1][2];

	inv.mat[2][3] = -mat[0][0] * mat[1][1] * mat[2][3] 
	+ mat[0][0] * mat[1][3] * mat[2][1] 
	+ mat[1][0] * mat[0][1] * mat[2][3] 
	- mat[1][0] * mat[0][3] * mat[2][1] 
	- mat[2][0] * mat[0][1] * mat[1][3] 
	+ mat[2][0] * mat[0][3] * mat[1][1];

	inv.mat[3][3] = mat[0][0] * mat[1][1] * mat[2][2] 
	- mat[0][0] * mat[1][2] * mat[2][1] 
	- mat[1][0] * mat[0][1] * mat[2][2] 
	+ mat[1][0] * mat[0][2] * mat[2][1] 
	+ mat[2][0] * mat[0][1] * mat[1][2] 
	- mat[2][0] * mat[0][2] * mat[1][1];

	float det = mat[0][0] * inv.mat[0][0] 
	+ mat[0][1] * inv.mat[1][0] 
	+ mat[0][2] * inv.mat[2][0] 
	+ mat[0][3] * inv.mat[3][0];

	if (det == 0)
		return *this;

	det = 1.0 / det;

	for (int y = 0; y < 4; y++)
	{
		inv.mat[y] *= det;
	}

	return inv;
}
