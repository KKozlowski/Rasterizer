#pragma once

#include "Color.h"
#include <string>
#include <vector>

struct material
{
	Color specular = {1,1,1,1};
	float shininess = 22.f;
};
