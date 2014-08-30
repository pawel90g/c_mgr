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
	int i, j;
	time_t start_time, end_time;

	init();

	set_number_of_threads(2);

	start_time = time(NULL);
	matrix = neighborhood_matrix_generator(1000, SMALL);
	end_time = time(NULL);

	/*
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%.2lf\t", matrix[i][j]);
		}
		printf("\n\n");
	}
	*/

	printf("Computing time = %f", difftime(end_time, start_time));

	system("PAUSE");
}