#pragma once

#include "Mesh.h"
#include "Buffer.h"
#include "mat4.h"
#include <vector>

class Painter
{
public:
	void FillTriangle(Triangle *tri, Buffer &buf);
	std::vector<Light*> lights;

private:
	Float4 viewVector;
	Float4 halfVector;
	Color Shade(Triangle *tri, RaycastHit &test);
	void MinMax(Triangle *tri, float &xMin, float &yMin, float &xMax, float &yMax);
};
