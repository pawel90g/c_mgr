#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

#include "settings.h"
#include "floyd_warshall_algorithm.h"

void floyd_warshall(double **graph, long graph_size)
{
	long i, j, k = 0;
	double temp = 0;
	double **temp_tab;


	for (i = 0; i < graph_size; i++)
	{
		graph[i][i] = 0;
	}

	temp_tab = (double **)malloc(sizeof(double*) * graph_size);

	for (i = 0; i < graph_size; i++)
	{
		temp_tab[i] = (double*)malloc(sizeof(double) * graph_size);
	}

	while (k < graph_size)
	{
		for (i = 0; i < graph_size; i++)
		{
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

		for (i = 0; i < graph_size; i++)
		{
			for (j = 0; j < graph_size; j++)
			{
				graph[i][j] = temp_tab[i][j];
			}
		}
		k++;
	}
}