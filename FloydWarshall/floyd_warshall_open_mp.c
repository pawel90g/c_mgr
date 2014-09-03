#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

#include "settings.h"
#include "floyd_warshall_open_mp.h"

void print_matrix(double **matrix, int matrix_size)
{
	int i, j = 0;

	for (i = 0; i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
		{
			printf("%.1f ", matrix[i][j] == -10000 ? -1 : matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
}

void floyd_warshall(double **graph, long graph_size)
{
	long i, j, k = 0;
	double temp = 0;
	double **temp_tab;

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
	for (i = 0; i < graph_size; i++)
	{
		graph[i][i] = 0;
	}

	temp_tab = (double **)malloc(sizeof(double*) * graph_size);

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
	for (i = 0; i < graph_size; i++)
	{
		temp_tab[i] = (double*)malloc(sizeof(double) * graph_size);
	}

	for (k = 0; k < graph_size; k++)
	{
#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
		for (i = 0; i < graph_size; i++)
		{
#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
			for (j = 0; j < graph_size; j++)
			{
				double delta = graph[i][k] + graph[k][j];

				if (graph[i][k] == -10000 || graph[k][j] == -10000)
				{
					temp_tab[i][j] = graph[i][j];
				}
				else if (graph[i][j] == -10000)
				{
					temp_tab[i][j] = delta;
				}
				else
				{
					temp_tab[i][j] = min(graph[i][j], delta);
				}
			}
		}

#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
		for (i = 0; i < graph_size; i++)
		{
#pragma omp parallel for num_threads(number_of_threads == 0 ? graph_size : number_of_threads)
			for (j = 0; j < graph_size; j++)
			{
				graph[i][j] = temp_tab[i][j];
			}
		}
	}
}