#define _USE_MATH_DEFINES
#include "Light.h"
#include <algorithm>

Float4 Light::GetVector(Float4 to)
{
    if(type == LightType::Directional)
        return direction;
	else
		return origin - to;
}

float Light::GetPower(Float4 vec)
{

    if(type == LightType::Directional)
        return 1.0f;
	else
    {
		float dist = vec.Magnitude();

        float power = 1.0f / (1.0f  + (dist * this->attenuation));

        if(type == LightType::Point)
            return power;

        float DV = normalizedDirection.Dot(-vec.GetNormalized());

		static float PiInv180 = 3.14159f / 180;

        if(DV < (90 - cutoff )* PiInv180)
            return 0.0f;

		if (power > 0)
			return std::pow(DV, spotlightExponent) * power;
		else return 0;
    }
}

