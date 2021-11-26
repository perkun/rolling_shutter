#include "Vec2.h"

Vec2 construct_vec2(double x, double y)
{
    Vec2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

double length(Vec2 v)
{ return sqrt(v.x * v.x + v.y * v.y); }
