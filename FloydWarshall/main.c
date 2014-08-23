#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "floyd_warshall_algorithm.h"
#include "graph_generator.h"

void main(void)
{
	double **matrix;
	int i, j;

	init_generator();
	matrix = neighborhood_matrix_generator(10, SMALL);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%.2lf\t", matrix[i][j]);
		}
		printf("\n\n");
	}

	system("PAUSE");
}