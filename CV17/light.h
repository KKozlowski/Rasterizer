#pragma once
#include "Color.h"

enum class LightType
{
	Point,
	Spotlight,
	Directional
};

struct Light
{
    Light(Float4 orig, LightType lightType, Float4 dir = {0,0,0,0}) : origin(orig), type(lightType), direction(dir), normalizedDirection(dir.GetNormalized()) { }
    Float4 origin;
    Float4 direction;
	Float4 normalizedDirection;
    float cutoff = 0.0f;
    float spotlightExponent = 1.0f;

	LightType type;

    Color ambient;
    Color diffuse;
    Color specular;

    float attenuation = 0.0f;

    Float4 GetVector(Float4 to);
    float GetPower(Float4 vec);
};