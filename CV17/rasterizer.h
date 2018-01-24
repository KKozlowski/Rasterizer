#pragma once

#include "Buffer.h"
#include "transformator.h"
#include "painter.h"

class Rasterizer
{
public:
	Rasterizer(int width, int height);

	void Render(std::vector<Mesh> &objects, std::vector<Light *> &lights);
	Buffer buf;

	static float RandomFloat(float min, float max);
private:

	Float4 OX = { 1.0f, 0.0f, 0.0f };
	Float4 OY = { 0.0f, 1.0f, 0.0f };
	Float4 OZ = { 0.0f, 0.0f, 1.0f };

	
	Transformator tr;
	Painter painter;

	
};