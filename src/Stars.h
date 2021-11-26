#ifndef _STARS_
#define _STARS_
#include "Vec2.h"

typedef struct
{
    int nr, sum, max_pixel;
    Vec2 position;
    double elongation;
} Star;

typedef struct
{
    Star *stars;
    int num_stars;
} StarCollection;

StarCollection copy_star_collection(const StarCollection *sc);
void destroy_star_collection(StarCollection *star_collection);

#endif
