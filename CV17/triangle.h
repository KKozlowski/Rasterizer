#pragma once

#include "Light.h"
#include "Color.h"
#include <string>
#include <vector>
#include "material.h"

/*        B
 *       /\
 *      /  \
 *  AB /    \ BC
 *    /      \
 *   /________\
 *  A    AC    C
 */



struct Vertex
{
    Vertex(float x, float y, float z): position(x,y,z) { }
	Vertex(Float4 _pos, Float4 _norm) 
		:position(_pos), normal(_norm)
	{}
    Float4 position;
    Float4 positionInView;
    Float4 normal;
    Color  col;

	virtual ~Vertex(){}
};

struct RaycastHit{
    bool hit;
    Float4 lambda;
};

struct Triangle
{
    Vertex *a,*b,*c;
    material* mat;

    Triangle(Vertex *_a, Vertex *_b, Vertex * _c);
    RaycastHit Intersect(float x, float y);

	virtual ~Triangle();
};