#include "Stars.h"

StarCollection copy_star_collection(const StarCollection *sc)
{
	StarCollection new_star_collection;
	new_star_collection.num_stars = sc->num_stars;
	new_star_collection.stars = malloc(sc->num_stars * sizeof(Star));
	for (int i = 0; i < sc->num_stars; i++)
	{
		new_star_collection.stars[i] = sc->stars[i];
	}
	return new_star_collection;
}

void destroy_star_collection(StarCollection *star_collection)
{
	free(star_collection->stars);
}

