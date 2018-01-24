#pragma once

#include "Mesh.h"
#include "Light.h"
#include <vector>
#include "mat4.h"


class Transformator
{
public:
	void SetIdentity();

	void Translate(Float4 Tv);
	void Rotate(float a, Float4 Rv);
	void Scale(Float4 Sv);

	void LookAt(Float4 up, Float4 eye, Float4 target);

	void Perspective(float fov, float ratio, float near, float far);

	std::vector<Vertex*> vertexBuffer;
	std::vector<Light*>  lightBuffer;

	void Transform();
	void TransformLight();
	void TransformVertex(Vertex* v);
private:
	Mat4x4 Obj2World;
	Mat4x4 World2View;
	Mat4x4 View2Perspective;

	Mat4x4 Obj2View;
	Mat4x4 Obj2ViewT;
	Mat4x4 Obj2Perspective;
};
