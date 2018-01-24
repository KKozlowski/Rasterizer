#include "Rasterizer.h"
#include <iostream>
#include <ctime>

Rasterizer::Rasterizer(int width, int height)
{
	buf.Init(width, height);
	tr.SetIdentity();
}

float Rasterizer::RandomFloat(float min, float max)
{
	return min + ((rand() % 1000)*0.001f) * (max - min);
}

void Rasterizer::Render(std::vector<Mesh>& objects, std::vector<Light*>& lights)
{
	buf.Clear();

	tr.lightBuffer = lights;
	tr.TransformLight();
	clock_t begin = std::clock();
	Float4 up(0.0f, 1.0f, 0.0f);
	Float4 eye(0.0f, -0.0f, -0.8f);
	Float4 target(0.0f, 0.0f, 0.0f);

	Float4 viewDir = { 0,0,1,0 };

	for (int o = 0; o < objects.size(); o++)
	{
		tr.SetIdentity();
		tr.LookAt(up, eye, target);
		tr.Perspective(60.0f, buf.width*1.0f / buf.height, 0.1, 100);

		tr.vertexBuffer = objects[o].vertices;

		tr.Scale(objects[o].Sv);

		tr.Rotate(objects[o].Rv.x, OX);
		tr.Rotate(objects[o].Rv.y, OY);
		tr.Rotate(objects[o].Rv.z, OZ);

		tr.Translate(objects[o].Tv);

		tr.Transform();

		painter.lights = lights;

		if (buf.width>0 && buf.height > 0) {
			
			
			for (int i = 0; i < objects[o].triangles.size(); i++)
			{
				Triangle *tri = objects[o].triangles[i];

				if ((tri->a->position - tri->b->position).Cross(tri->c->position - tri->b->position).Dot3(viewDir) > 0)
					painter.FillTriangle(tri, buf);
			}
		}
	}

	clock_t end = std::clock();

	clock_t time = end - begin;

	buf.calculationsTime = time;
}