#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "file_reader_writer.h"

configuration_data parse_data_from_file(char *data)
{
	int data_len;
	int i, j, k;

	int start_index = 0, end_index = 0;
	char *number_in_char_array;

	int readed_numbers[4];
	int actual_number_index = 0;

	configuration_data config_data;

	data_len = _mbstrlen(data);

	for (i = 0; i < data_len; i++)
	{
		if (((int)data[i]) == 32 ||
			(i == (data_len - 1) &&
			((int)data[i]) != 32) ||
			data[i] == '\n')
		{
			end_index = i;

			if (end_index != start_index)
			{
				number_in_char_array = (char*)malloc(sizeof(char) * (end_index - start_index));

				for (j = 0, k = start_index; j < end_index - start_index; j++, k++)
				{
					number_in_char_array[j] = data[k];
				}
			}
			else
			{
				number_in_char_array = (char*)malloc(sizeof(char));
				number_in_char_array[0] = data[end_index];
			}

			readed_numbers[actual_number_index] = (int)strtol(number_in_char_array, NULL, 10);
			actual_number_index++;

			start_index = i + 1;
		}
	}

	config_data.graph_generator_type = readed_numbers[0] ? readed_numbers[0] : 0;
	config_data.matrix_size = readed_numbers[1] ? readed_numbers[1] : 0;
	config_data.number_of_threads = readed_numbers[2] ? readed_numbers[2] : 0;
	config_data.distribution_threads_model = readed_numbers[3] ? readed_numbers[3] : 0;

	return config_data;
}

int get_size_in_characters(int number_to_convert)
{
	if (number_to_convert % 10000 > 1) return 5;
	if (number_to_convert % 1000 > 1) return 4;
	if (number_to_convert % 100 > 1) return 3;
	if (number_to_convert % 10 > 1) return 2;
	return 1;
}

void save_computing_data(const char *file_path, data_to_save *computing_data, int computing_data_size)
{
	FILE *result_file;
	errno_t err;
	int i;

	char *graph_generator_type_char;
	char *number_of_threads_char;
	char *matrix_size_char;
	char *distribution_threads_model_char;
	char *computing_start_time_char;
	char *computing_end_time_char;

	err = fopen_s(&result_file, file_path, "at");
	if (err)
	{
		// TODO error handling
	}

	for (i = 0; i < computing_data_size; i++)
	{
		graph_generator_type_char = (char*)malloc(sizeof(char) * get_size_in_characters(computing_data[i].graph_generator_type));
		number_of_threads_char = (char*)malloc(sizeof(char) * get_size_in_characters(computing_data[i].number_of_threads));
		matrix_size_char = (char*)malloc(sizeof(char) * get_size_in_characters(computing_data[i].matrix_size));
		distribution_threads_model_char = (char*)malloc(sizeof(char) * get_size_in_characters(computing_data[i].distribution_threads_model));

		computing_start_time_char = (char*)malloc(sizeof(char) * 26);
		computing_end_time_char = (char*)malloc(sizeof(char) * 26);
		

		_itoa_s(computing_data[i].graph_generator_type, graph_generator_type_char, sizeof(graph_generator_type_char), 10);
		_itoa_s(computing_data[i].number_of_threads, number_of_threads_char, sizeof(number_of_threads_char), 10);
		_itoa_s(computing_data[i].matrix_size, matrix_size_char, sizeof(matrix_size_char), 10);
		_itoa_s(computing_data[i].distribution_threads_model, distribution_threads_model_char, sizeof(distribution_threads_model_char), 10);

		ctime_s(computing_start_time_char, 26, &computing_data[i].computing_start_time);
		ctime_s(computing_end_time_char, 26, &computing_data[i].computing_end_time);
		
		// TODO create line to write

		// TODO check it if it is correct
		free(graph_generator_type_char);
		free(number_of_threads_char);
		free(matrix_size_char);
		free(distribution_threads_model_char);
		free(computing_start_time_char);
		free(computing_end_time_char);
	}
}

configuration_data *load_configuration_data(const char *file_path, int number_of_scenarios)
{
	FILE *config_file;
	errno_t err;
	configuration_data *scenarios;

	char line[128];
	int buffor_size = 128;
	int i = 0;

	err = fopen_s(&config_file, file_path, "rt");
	if (err)
	{
		// TODO error handling
	}

	scenarios = (configuration_data*)malloc(sizeof(configuration_data)*number_of_scenarios);

	for (i = 0; i < number_of_scenarios; i++)
	{
		fgets(line, buffor_size, config_file);
		scenarios[i] = parse_data_from_file(line);
	}

	return scenarios;
}