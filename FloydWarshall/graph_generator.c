#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph_generator.h"

void init_generator()
{
	srand(time(NULL));
}

double** neighborhood_matrix_generator(unsigned long graph_size, t_intensity intensity)
{
	unsigned long i, j;
	double **neighborhood_matrix = (double**)malloc(sizeof(double*) * graph_size);
	int is_road_available = 0;
	double road_occurance_probability = 0;

	for (i = 0; i < graph_size; i++)
	{
		neighborhood_matrix[i] = (double*)malloc(sizeof(double) * graph_size);
	}

	for (i = 0; i < graph_size; i++)
	{
		for (j = i; j < graph_size; j++)
		{
			if (i == j)
			{
				neighborhood_matrix[i][j] = 0;
				continue;
			}
			road_occurance_probability = road_occurance_generator();

			if ((road_occurance_probability > SMALL_INTENSITY_RATIO && intensity == SMALL) ||
				(road_occurance_probability > HUGE_INTENSITY_RATIO && intensity == HUGE))
				neighborhood_matrix[i][j] = distance_generator();
			else
				neighborhood_matrix[i][j] = INACCESSIBLE_ROAD_SYMBOL;
		}
	}

	for (i = 1; i < graph_size; i++)
	{
		for (j = 0; j < i; j++)
		{
			road_occurance_probability = road_occurance_generator();

			if ((road_occurance_probability > SMALL_INTENSITY_RATIO && intensity == SMALL) ||
				(road_occurance_probability > HUGE_INTENSITY_RATIO && intensity == HUGE))
				if (neighborhood_matrix[j][i] == INACCESSIBLE_ROAD_SYMBOL)
					neighborhood_matrix[i][j] = distance_generator();
				else
					neighborhood_matrix[i][j] = neighborhood_matrix[j][i];
			else
				neighborhood_matrix[i][j] = INACCESSIBLE_ROAD_SYMBOL;
		}
	}

	return neighborhood_matrix;
}

double road_occurance_generator()
{
	int i;
	double random_numbers_table[2000] = { 0.0 };

	for (i = 0; i < 2000; i++) {
		random_numbers_table[i] = (double)(rand() % 1000) / 1000;

		double delta = (double)(rand() % 200) / 200;

		if ((random_numbers_table[i] + delta) <= 1)
			random_numbers_table[i] += delta;
	}

	return random_numbers_table[rand() % 2000];
}

double distance_generator()
{
	int i;
	double random_distance_table[2000] = { 0.0 };

	for (i = 0; i < 2000; i++) {
		random_distance_table[i] = (double)(rand() % 60000) / 100;

		if (random_distance_table[i] < 10.0)
			random_distance_table[i] += (double)(rand() % 3000) / 100;
	}

	return random_distance_table[rand() % 2000];
}

