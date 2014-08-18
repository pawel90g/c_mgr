#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "floyd_warshall_algorithm.h"

void main(void)
{
	double **tab = (double**)malloc(4 * sizeof(double*));

	for (int i = 0; i < 4; i++)
	{
		tab[i] = (double*)malloc(4 * sizeof(double));
	}

	tab[0][0] = -10000;
	tab[0][1] = 4;
	tab[0][2] = 3;
	tab[0][3] = -10000;

	tab[1][0] = -10000;
	tab[1][1] = -10000;
	tab[1][2] = -2;
	tab[1][3] = -5;

	tab[2][0] = -10000;
	tab[2][1] = 1;
	tab[2][2] = -10000;
	tab[2][3] = -10000;

	tab[3][0] = -10000;
	tab[3][1] = -10000;
	tab[3][2] = 2;
	tab[3][3] = 2;

	floyd_warshall(tab, 4);

	for (int i = 0; i < 4; i++)
	{
		free(tab[i]);
	}

	free(tab);

	system("PAUSE");
}