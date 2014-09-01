#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "settings.h"
#include "graph_generator.h"

double** neighborhood_matrix_generator(long graph_size, t_intensity intensity)
{
	long i, j;
	double **neighborhood_matrix = (double**)malloc(sizeof(double*) * graph_size);
	int is_road_available = 0;
	double road_occurance_probability = 0;

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
	for (i = 0; i < graph_size; i++)
	{
		neighborhood_matrix[i] = (double*)malloc(sizeof(double) * graph_size);
	}

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
	for (i = 0; i < graph_size; i++)
	{
#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
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

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
	for (i = 1; i < graph_size; i++)
	{
#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
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
	double random_numbers_table[GENERATOR_INTERATIONS] = { 0.0 };

#pragma omp parallel for num_threads(number_of_threads == 0 ? GENERATOR_INTERATIONS : number_of_threads)
	for (i = 0; i < 2000; i++) {
		random_numbers_table[i] = (double)(rand() % 1000) / 1000;

		double delta = (double)(rand() % 200) / 200;

		if ((random_numbers_table[i] + delta) <= 1)
			random_numbers_table[i] += delta;
	}

	return random_numbers_table[rand() % GENERATOR_INTERATIONS];
}

double distance_generator()
{
	int i;
	double random_distance_table[GENERATOR_INTERATIONS] = { 0.0 };

#pragma omp parallel for num_threads(number_of_threads == 0 ? GENERATOR_INTERATIONS : number_of_threads)
	for (i = 0; i < GENERATOR_INTERATIONS; i++) {
		random_distance_table[i] = (double)(rand() % 60000) / 100;

		if (random_distance_table[i] < 10.0)
			random_distance_table[i] += (double)(rand() % 3000) / 100;
	}

	return random_distance_table[rand() % GENERATOR_INTERATIONS];
}

