#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#include "floyd_warshall_algorithm.h"
#include "graph_generator.h"

void main(void)
{
	double **matrix;
	int i, j = 0;
	time_t start_time, end_time;
	int steps[5] = { 1, 2, 3, 4, 0 };

	init();


	printf("Generating matrix with %d threads ... \n", steps[3]);
	start_time = time(NULL);
	matrix = neighborhood_matrix_generator(1000, SMALL);
	end_time = time(NULL);

	printf("Generating time = %f\n", difftime(end_time, start_time));

	for (i = 0; i < 5; i++)
	{
		set_number_of_threads(steps[i]);

		printf("Computing with %d threads ... \n", steps[i]);
		start_time = time(NULL);
		floyd_warshall(matrix, 1000);
		end_time = time(NULL);

		printf("\n\n");
		printf("Computing time = %f", difftime(end_time, start_time));
		printf("\n\n");

		printf("------------------------------------\n\n");
	}

	system("PAUSE");
}