#pragma once
#include "Triangle.h"
#include <map>

struct Mesh
{
	Mesh(){}
    std::vector<Vertex*> vertices;
    std::vector<Triangle*> triangles;

	virtual ~Mesh();

    Float4 Tv = {0.0f, 0.0f, 0.0f};
    Float4 Rv = {0.0f, 0.0f, 0.0f};
    Float4 Sv = {1.0f, 1.0f, 1.0f};

	static Mesh Cube();
	static Mesh Cylinder();
	static Mesh HalfGeosphere();

	void release();
};