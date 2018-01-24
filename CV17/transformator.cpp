#include "transformator.h"
#include <iostream>
#include <corecrt_math_defines.h>

void Transformator::SetIdentity()
{
	Obj2World = Mat4x4::identity();
	World2View = Mat4x4::identity();
	View2Perspective = Mat4x4::identity();
}

void Transformator::Translate(Float4 v)
{
	Mat4x4 T = { { { 1, 0, 0, v.x },
	{ 0, 1, 0, v.y },
	{ 0, 0, 1, v.z },
	{ 0, 0, 0, 1 } } };
	Obj2World = T*Obj2World;
}

void Transformator::Scale(Float4 v)
{
	Mat4x4 S = { { { v.x, 0,   0,   0 },
	{ 0,   v.y, 0,   0 },
	{ 0,   0,   v.z, 0 },
	{ 0,   0,   0,   1 } } };
	Obj2World = S*Obj2World;
}

void Transformator::Rotate(float a, Float4 v)
{
	static float rad = M_PI / 180.0f;

	float s = std::sin(a*rad), c = std::cos(a*rad);

	v.NormalizeThis();

	Mat4x4 R = { { 
		{ v.x*v.x*(1 - c) + c     , v.x*v.y*(1 - c) - v.z*s , v.x*v.z*(1 - c) + v.y*s , 0 },
		{ v.x*v.y*(1 - c) + v.z*s , v.y*v.y*(1 - c) + c     , v.z*v.y*(1 - c) - v.x*s , 0 },
		{ v.x*v.z*(1 - c) - v.y*s , v.z*v.y*(1 - c) + v.x*s , v.z*v.z*(1 - c) + c     , 0 },
		{ 0						  , 0                       , 0                       , 1 } } };

	Obj2World = R*Obj2World;
}

void Transformator::LookAt(Float4 up, Float4 eye, Float4 target)
{
	up.NormalizeThis();
	Float4 forward = (target- eye).GetNormalized();
	Float4 right = up.Cross(forward).GetNormalized();
	up = forward.Cross(right);

	Mat4x4 Mov = { { 
		{ 1, 0, 0, -eye.x },
		{ 0, 1, 0, -eye.y },
		{ 0, 0, 1, -eye.z },
		{ 0, 0, 0, 1 } 
	} };

	Mat4x4 Rot = { { 
		{ right.x,    right.y,    right.z,    0 },
		{ up.x,       up.y,       up.z,       0 },
		{ -forward.x, -forward.y, -forward.z, 0 },
		{ 0,          0,          0,          1 } 
	} };

	World2View = Rot*Mov;
}

void Transformator::Perspective(float fov, float ratio, float near, float far)
{
	if (far == near)
		return;
	float f_n = 1.0f / (near - far);
	fov *= M_PI / 360;
	float s = std::sin(fov);
	float f = s != 0 ? std::cos(fov) / s : std::cos(fov) / 0.0001f;
	ratio = 1.0f / ratio;

	View2Perspective = { { 
	{ f*ratio,  0,  0,                 0 },
	{ 0,        f,  0,                 0 },
	{ 0,        0,  (far + near)*f_n,  (2 * far*near)*f_n },
	{ 0,        0,  -1,                0 } 
	} };
}

void Transformator::Transform()
{
	Obj2View = World2View*Obj2World;
	Obj2Perspective = View2Perspective*Obj2View;
	Obj2ViewT = Obj2View.Inversed();
	Obj2ViewT.TransposeThis();

	for (int i = 0; i < vertexBuffer.size(); i++)
	{
		TransformVertex(vertexBuffer[i]);
	}
}

void Transformator::TransformLight()
{
	Mat4x4 VT = World2View.Inversed();
	VT.TransposeThis();

	for (int i = 0; i < lightBuffer.size(); i++)
	{
		lightBuffer[i]->origin *= (World2View);
		lightBuffer[i]->direction *= (VT);
		lightBuffer[i]->normalizedDirection = lightBuffer[i]->direction.GetNormalized();
	}
}

void Transformator::TransformVertex(Vertex *v)
{
	v->positionInView = v->position * Obj2View;

	v->position *= Obj2Perspective;
	v->position /= v->position.w;

	v->normal *= Obj2ViewT;
}
