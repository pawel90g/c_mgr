#ifndef _GRAPH_GENERATOR_
#define _GRAPH_GENERATOR_

#define SMALL_INTENSITY_RATIO 0.85
#define HUGE_INTENSITY_RATIO 0.55
#define INACCESSIBLE_ROAD_SYMBOL -1.0

typedef enum
{
	SMALL = 0,
	HUGE = 1,
} t_intensity;

void init_generator();
double road_occurance_generator();
double distance_generator();
double** neighborhood_matrix_generator(unsigned long graph_size, t_intensity intensity);

#endif _GRAPH_GENERATOR_