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

#define SCENARIOS_FILE_NAME "scenarios.txt"
#define RESULTS_FILE_NAME "computing_results.csv"

char *get_dir_from_file_path(char *path)
{
	int i = 0, j = 0;
	size_t path_size;
	char *dir;

	path_size = strlen(path);

	dir = (char*)malloc(sizeof(char)* (path_size + 1));

	for (i = path_size - 1; i > 0; i--)
	{
		if (path[i] == '\\') break;
	}

	for (j = 0; j < i + 1; j++)
	{
		dir[j] = path[j];
	}

	dir[j] = '\0';

	return dir;
}

char *prepare_file_path(char *app_path, char *file_name)
{
	int i = 0;
	size_t file_dir_size;
	size_t file_name_size;
	char *prepared_file_path;
	char *file_dir;

	file_dir = get_dir_from_file_path(app_path);

	file_dir_size = strlen(file_dir);
	file_name_size = strlen(file_name);

	prepared_file_path = (char*)malloc(sizeof(char) * (file_dir_size + file_name_size + 2));

	memcpy(prepared_file_path, file_dir, file_dir_size);
	memcpy(&prepared_file_path[file_dir_size], file_name, file_name_size);
	memcpy(&prepared_file_path[file_dir_size + file_name_size], "\0", 1);

	return prepared_file_path;
}

void main(int argc, const char* argv[])
{
	double **matrix;
	int current_matrix_size = -1, current_generator_type = -1;
	int x, i, j = 0;
	time_t start_time, end_time;
	configuration_data *scenarios;
	data_to_save *computing_result;

	init();

	scenarios = load_configuration_data(prepare_file_path(argv[0], SCENARIOS_FILE_NAME), NUMBER_OF_SCENARIOS);
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

	save_computing_data(prepare_file_path(argv[0], RESULTS_FILE_NAME), computing_result, 40);

	system("PAUSE");
}