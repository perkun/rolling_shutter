#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vec2.h"
#include "Stars.h"


typedef struct
{
	double readout_time; // in seconds

} CameraConfig;


typedef struct
{
    /* direction of the backgroud in image ref. frame */
    Vec2 background_direction; // px/s

} FrameConfig;


StarCollection import_stars(char filename[]);
StarCollection eliminate_rolling_shutter(const StarCollection *star_collection,
                               const FrameConfig frame_cfg,
                               const CameraConfig camera_cfg);


int main(int argc, char *argv[])
{
    FrameConfig frame_cfg;
    frame_cfg.background_direction = construct_vec2(3, 10);

    CameraConfig camera_cfg;
    camera_cfg.readout_time = 0.02;

    StarCollection star_collection = import_stars(
        "../data/b210308_223511_1002_GPS_40294.fits_b.fits_xy.txt");


    StarCollection fixed_stars =
        eliminate_rolling_shutter(&star_collection, frame_cfg, camera_cfg);


    //     for (int i = 0; i < fixed_stars.num_stars; i++)
    //     {
    //         printf("%lf %lf\n", star_collection.stars[i].position.x,
    //                star_collection.stars[i].position.y);
    //     }

    for (int i = 0; i < fixed_stars.num_stars; i++)
    {
        Vec2 diff;
        diff.x = star_collection.stars[i].position.x -
                 fixed_stars.stars[i].position.x;
        diff.y = star_collection.stars[i].position.y -
                 fixed_stars.stars[i].position.y;
        printf("pos: %lf %lf -> %lf %lf  | diff: %lf\n",
			star_collection.stars[i].position.x,
               star_collection.stars[i].position.y,
			fixed_stars.stars[i].position.x,
               fixed_stars.stars[i].position.y,
			   length(diff));
    }

    destroy_star_collection(&star_collection);
    destroy_star_collection(&fixed_stars);
    return 0;
}


StarCollection import_stars(char filename[])
{
	StarCollection star_collection;

    FILE *f = fopen(filename, "r");
    char line[201];
    int num_lines = 0;

    if (!f)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    while (fgets(line, 200, f))
    {
        num_lines++;
    }
    int num_stars = num_lines - 1;

    if (num_stars < 1)
    {
        printf("Empty file, nothing to do...\n");
        exit(0);
    }

	star_collection.num_stars = num_stars;
    star_collection.stars = malloc(num_stars * sizeof(Star));
    fseek(f, 0, SEEK_SET);
    fgets(line, 200, f); // comment at the top
    int i = 0;
    while (fgets(line, 200, f))
    {
		Star *star = &star_collection.stars[i];
        sscanf(line, "%d %lf %lf %d %d %lf", &star->nr, &star->position.x,
               &star->position.y, &star->sum, &star->max_pixel,
               &star->elongation);
        i++;
    }


    fclose(f);
	return star_collection;
}


StarCollection eliminate_rolling_shutter(const StarCollection *star_collection,
                               const FrameConfig frame_cfg,
                               const CameraConfig camera_cfg)
{
	StarCollection fixed_collection = copy_star_collection(star_collection);
    for (int i = 0; i < star_collection->num_stars; i++)
    {
        Vec2 *pos = &(fixed_collection.stars[i].position);
        pos->x -=
            frame_cfg.background_direction.x * pos->y * camera_cfg.readout_time;
        pos->y -=
            frame_cfg.background_direction.y * pos->y * camera_cfg.readout_time;
    }
	 return fixed_collection;
}

