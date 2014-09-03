#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#include "floyd_warshall_open_mp.h"
#include "graph_generator.h"
#include "file_reader_writer.h"
#include "settings.h"

#define NUMBER_OF_SCENARIOS 40

void main(int argc, const char* argv[])
{
	double **matrix;
	int current_matrix_size = -1, current_generator_type = -1;
	int x, i, j = 0;
	time_t start_time, end_time;
	configuration_data *scenarios;
	data_to_save *computing_result;

	init();

	scenarios = load_configuration_data("E:\\mgr\\scenarios.txt", NUMBER_OF_SCENARIOS);
	computing_result = (data_to_save*)malloc(sizeof(data_to_save)*NUMBER_OF_SCENARIOS);

	current_generator_type = scenarios[0].graph_generator_type;
	current_matrix_size = scenarios[0].matrix_size;
	matrix = neighborhood_matrix_generator(current_matrix_size, current_generator_type);

	for (x = 0; x < NUMBER_OF_SCENARIOS; x++)
	{
		if (current_matrix_size != scenarios[x].matrix_size ||
			current_generator_type != scenarios[x].graph_generator_type)
		{
			current_generator_type = scenarios[x].graph_generator_type;
			current_matrix_size = scenarios[x].matrix_size;

			matrix = neighborhood_matrix_generator(current_matrix_size, current_generator_type);
		}

		set_number_of_threads(scenarios[x].number_of_threads);

		start_time = time(NULL);
		floyd_warshall(matrix, current_matrix_size, scenarios[x].distribution_threads_model);
		end_time = time(NULL);

		computing_result[x].computing_start_time = start_time;
		computing_result[x].computing_end_time = end_time;
		computing_result[x].distribution_threads_model = scenarios[x].distribution_threads_model;
		computing_result[x].graph_generator_type = scenarios[x].graph_generator_type;
		computing_result[x].matrix_size = scenarios[x].matrix_size;
		computing_result[x].number_of_threads = scenarios[x].number_of_threads;
	}

	save_computing_data("E:\\mgr\\computing_results.csv", computing_result, 40);

	system("PAUSE");
}