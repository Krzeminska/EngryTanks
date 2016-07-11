#ifndef FLOAT2_H
#define FLOAT2_H

#include <math.h>

class float2
{
    public:
        float x, y;
        float2():x(0),y(0) {}
        float2(float _x, float _y):x(_x),y(_y) {}

        float2 operator*(float f) { return float2(x*f, y*f); }
        float2 operator/(float f) { return float2(x/f, y/f); }
        float2 &operator+=(float2 f) { x+=f.x; y+=f.y; return *this; }
        float2 operator-(float2 f) { return float2(x - f.x, y - f.y); }
        float2 operator+(float2 f) { return float2(x + f.x, y + f.y); }
        bool operator>(float2 f) { if(x > f.x || y > f.y) return true; return false;; }

        float2(float f);

        float2 normalized();

        void clampLen(float f);

        float len() { return sqrt(x*x+y*y); }

        void zero() { x=y=0.f; }
        bool isZero() { return x==0.f && y==0.f; }
    protected:
    private:
};

#endif // FLOAT2_H
