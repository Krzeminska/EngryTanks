#include "float2.h"

float2::float2(float f)
    :x(cos(f*0.01745f))
    ,y(sin(f*0.01745f))
{
}

float2 float2::normalized()
{
    if (fabs(x)<.001f && fabs(y)<.001f)
        return float2(0.f, 0.f);
    else
        return *this / sqrt(x*x+y*y);
}

void float2::clampLen(float f)
{
    if (fabs(x)<.001f && fabs(y)<.001f)
        return;
    float len = sqrt(x*x+y*y);
    if (len > f)
    {
        x *= f/len;
        y *= f/len;
    }
}
