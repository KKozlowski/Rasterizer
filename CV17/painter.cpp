#include "painter.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

void Painter::FillTriangle(Triangle *tri, Buffer &buf)
{
	float stepx = 1.f / buf.width;
	float stepy = 1.f / buf.height;

	float xMin, yMin, xMax, yMax;
	MinMax(tri, xMin, yMin, xMax, yMax);

	for (float y = yMin; y < yMax; y += stepy)
	{
		for (float x = xMin; x < xMax; x += stepx)
		{
		
			RaycastHit intersect = tri->Intersect(x, y);

			if (intersect.hit)
			{
				float depth = (tri->a->position.z * intersect.lambda.x) + (tri->b->position.z * intersect.lambda.y) + (tri->c->position.z * intersect.lambda.z);

				if (depth >= 0 && depth <= 1)
				{
					int xInBuffer = (x + 1) * buf.width * 0.5f, yInBuffer = (y + 1) * buf.height * 0.5f;
					float probedDepth = buf.depth[buf.width * yInBuffer + xInBuffer];
					if (depth < probedDepth || probedDepth == 1)
					{
						Color c = Shade(tri, intersect);

						buf.Write(xInBuffer, yInBuffer, c, depth);
					}
				}
			}
		}
	}
}

Color Painter::Shade(Triangle *tri, RaycastHit &test)
{
	float f1 = test.lambda[0];
	float f2 = test.lambda[1];
	float f3 = test.lambda[2];

	float divider = 1.0f / (f1 + f2 + f3);

	f1 *= divider;
	f2 *= divider;
	f3 *= divider;

	Color final = {0,0,0,0};
	Color base = tri->a->col * test.lambda[0] + tri->b->col * test.lambda[1] + tri->c->col * test.lambda[2];

	Color ambient = { 0,0,0,0 }, diffuse = { 0,0,0,0 }, specular = { 0,0,0,0 };

	Float4 pointInView(tri->a->positionInView * test.lambda[0] + tri->b->positionInView * test.lambda[1] + tri->c->positionInView * test.lambda[2]);
	Float4 normal(tri->a->normal * f1 + tri->b->normal * f2 + tri->c->normal * f3);
	normal.NormalizeThis();

	material* material = tri->mat;

	for (int i = 0; i < lights.size(); i++)
	{
		Light *l1 = lights[i];
		ambient = l1->ambient * base;

		Float4 lightVec = l1->GetVector(pointInView);
		float power = l1->GetPower(lightVec);

		lightVec.NormalizeThis();

		float LN = lightVec.Dot(normal);
		if (LN > 1)
			LN = 1;
		if (LN < 0)
			LN = 0;
		
		diffuse = (l1->diffuse * power * LN * base);

		viewVector = -(pointInView.GetNormalized());
		halfVector = (viewVector + -lightVec).GetNormalized();

		float NH = (halfVector.Dot3(normal));
		if (NH < 0) NH = 0;
		float shininess = material->shininess;

		float ex = std::pow(NH, shininess);

		specular =( l1->specular
			* material->specular
			* (ex
			* power));

		final = final + ambient + diffuse + specular;
	}
	return final;
}

void Painter::MinMax(Triangle *t, float &xMin, float &yMin, float &xMax, float &yMax)
{
	yMax = (t->a->position.y > t->b->position.y) ? t->a->position.y : t->b->position.y;
	xMax = (t->a->position.x > t->b->position.x) ? t->a->position.x : t->b->position.x;
	xMin = (t->a->position.x < t->b->position.x) ? t->a->position.x : t->b->position.x;
	yMin = (t->a->position.y < t->b->position.y) ? t->a->position.y : t->b->position.y;

	xMax = (xMax > t->c->position.x) ? xMax : t->c->position.x;
	xMin = (xMin < t->c->position.x) ? xMin : t->c->position.x;
	yMax = (yMax > t->c->position.y) ? yMax : t->c->position.y;
	yMin = (yMin < t->c->position.y) ? yMin : t->c->position.y;

	xMax>1 ? xMax = 1 : xMax<-1 ? xMax = -1 : false;
	yMax>1 ? yMax = 1 : yMax<-1 ? yMax = -1 : false;

	xMin>1 ? xMin = 1 : xMin<-1 ? xMin = -1 : false;
	yMin>1 ? yMin = 1 : yMin<-1 ? yMin = -1 : false;
}
