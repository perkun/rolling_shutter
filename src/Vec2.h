#ifndef _VEC2_
#define _VEC2_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct
{
	double x, y;
} Vec2;

Vec2 construct_vec2(double x, double y);
double length(Vec2 v);

#endif
