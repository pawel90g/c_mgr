#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

#include "floyd_warshall_open_mp.h"
#include "graph_generator.h"
#include "file_reader_writer.h"
#include "settings.h"

#define NUMBER_OF_SCENARIOS 2

#define SCENARIOS_FILE_NAME "scenarios.txt"
#define RESULTS_FILE_NAME "computing_results.csv"

char *prepare_file_path(char *app_path, char *file_name)
{
	int i = 0;
	size_t file_dir_size;
	size_t file_name_size;
	char *prepared_file_path;

	file_dir_size = strlen(app_path);
	file_name_size = strlen(file_name);

	prepared_file_path = (char*)malloc(sizeof(char) * (file_dir_size + file_name_size + 2));

	memcpy(prepared_file_path, app_path, file_dir_size);
	memcpy(&prepared_file_path[file_dir_size], "/", 1);
	memcpy(&prepared_file_path[file_dir_size + 1], file_name, file_name_size);
	memcpy(&prepared_file_path[file_dir_size + 1 + file_name_size], "\0", 1);

	return prepared_file_path;
}


int main(void)
{
	double **matrix;
	int current_matrix_size = -1, current_generator_type = -1;
	int x, i;
	time_t start_time, end_time;
	configuration_data *scenarios;
	data_to_save *computing_result;
	char *config_file_path;
	char app_dir_buffor[1024];

	init();

	if(getcwd(app_dir_buffor, sizeof(app_dir_buffor)) != NULL)
	{
		config_file_path = prepare_file_path(app_dir_buffor, SCENARIOS_FILE_NAME);
	}
	else
	{
		printf("An error occurred while parsing the path");
		return 1;
	}

	scenarios = load_configuration_data(config_file_path, NUMBER_OF_SCENARIOS);

	computing_result = (data_to_save*)malloc(sizeof(data_to_save)*NUMBER_OF_SCENARIOS);

	current_generator_type = scenarios[0].graph_generator_type;
	current_matrix_size = scenarios[0].matrix_size;

	set_number_of_threads(0);
	matrix = neighborhood_matrix_generator(current_matrix_size, current_generator_type);

	for (x = 0; x < NUMBER_OF_SCENARIOS; x++)
	{
		if (current_matrix_size != scenarios[x].matrix_size ||
			current_generator_type != scenarios[x].graph_generator_type)
		{
			if (matrix)
			{
				for (i = 0; i < current_matrix_size; i++)
				{
					free(matrix[i]);
				}
				free(matrix);
			}

			current_generator_type = scenarios[x].graph_generator_type;
			current_matrix_size = scenarios[x].matrix_size;

			set_number_of_threads(0);
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

	save_computing_data(prepare_file_path(app_dir_buffor, RESULTS_FILE_NAME), computing_result, NUMBER_OF_SCENARIOS);

	free(computing_result);
	free(scenarios);

	return 0;
}
