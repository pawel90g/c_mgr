#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#include "floyd_warshall_open_mp.h"
#include "graph_generator.h"
#include "file_reader_writer.h"

void main(int argc, const char* argv[])
{

	char *startup_path = argv[0];
	/*double **matrix;
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
	}*/

	int i = 0;
	long x;
	data_to_save d_s[1];
	d_s[0].matrix_size = 0;
	d_s[0].number_of_threads = 4;
	d_s[0].graph_generator_type = 1;
	d_s[0].distribution_threads_model = 0;
	d_s[0].computing_start_time = time(NULL);
	
	for (i = 0; i < INT_MAX; i++)
	{
		x = i * 2;
	}

	d_s[0].computing_end_time = time(NULL);

	save_computing_data("H:\\results.csv", d_s, 1);

	system("PAUSE");
}