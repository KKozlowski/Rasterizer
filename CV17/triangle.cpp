#include "Triangle.h"
#include "Color.h"
#include <iostream>

Triangle::Triangle(Vertex *_a, Vertex *_b, Vertex *_c)
	: a(_a), b(_b), c(_c), mat(new material())
{

}

RaycastHit Triangle::Intersect(float x, float y)
{
    RaycastHit value = {false, {0.0f, 0.0f, 0.0f} };

    float ABy = a->position.y - b->position.y;
    float ABx = a->position.x - b->position.x;
    float BCy = b->position.y - c->position.y;
    float CBx = c->position.x - b->position.x;
    float ACx = a->position.x - c->position.x;
    float CAy = c->position.y - a->position.y;

    float xc =  x - c->position.x;
    float yc =  y - c->position.y;

    float AB = ( ABx) * (y - a->position.y) - ABy * (x - a->position.x); // P1, P2, P
    float BC = (-CBx) * (y - b->position.y) - BCy * (x - b->position.x); // P2, P3, P
    float CA = (-ACx) * (yc) - (CAy) * (xc); // P3, P1, P

    value.hit = (
		(AB > 0 || (AB == 0 && (ABy > 0 || (ABy == 0 && ABx < 0)))) 
		&& (BC > 0 || (BC == 0 && (BCy > 0 || (BCy == 0 && CBx > 0)))) 
		&& (CA > 0 || (CA == 0 && (CAy > 0 || (CAy == 0 && ACx > 0))))
		);

    if( value.hit )
    {
        value.lambda[0] = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx) + (CBx * (-CAy)));
        value.lambda[1] = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
        value.lambda[2] = 1 - value.lambda[0] - value.lambda[1];

    }
    return value;
}

Triangle::~Triangle()
{
	//delete mat;
}