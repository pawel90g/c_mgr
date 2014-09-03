#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "file_reader_writer.h"

#define CTIME_ARRAY_SIZE 26
#define CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN 24
#define SEPARATOR_SIGN ";"

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
	if (number_to_convert > 9999 && number_to_convert <= 99999) return 5;
	if (number_to_convert > 999 && number_to_convert <= 9999) return 4;
	if (number_to_convert > 99 && number_to_convert <= 999) return 3;
	if (number_to_convert > 9 && number_to_convert <= 99) return 2;
	return 1;
}

char *prepare_line_to_write(data_to_save computing_data)
{
	char *graph_generator_type_char;
	char *number_of_threads_char;
	char *matrix_size_char;
	char *distribution_threads_model_char;
	char *computing_start_time_char;
	char *computing_end_time_char;

	int graph_generator_type_array_size;
	int number_of_threads_array_size;
	int matrix_size_array_size;
	int distribution_threads_model_array_size;

	int offset = 0, i = 0;

	char *line_array;

	// get size in charakters of numbers
	graph_generator_type_array_size = get_size_in_characters(computing_data.graph_generator_type);
	number_of_threads_array_size = get_size_in_characters(computing_data.number_of_threads);
	matrix_size_array_size = get_size_in_characters(computing_data.matrix_size);
	distribution_threads_model_array_size = get_size_in_characters(computing_data.distribution_threads_model);

	// alloc memory for final array
	line_array = (char*)malloc(sizeof(char) *(graph_generator_type_array_size + number_of_threads_array_size + matrix_size_array_size + distribution_threads_model_array_size + (2 * CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN) + 5 + 2));

	// alloc memory for partial data arrays
	graph_generator_type_char = (char*)malloc(sizeof(char) * 2 * graph_generator_type_array_size);
	number_of_threads_char = (char*)malloc(sizeof(char) * 2 * number_of_threads_array_size);
	matrix_size_char = (char*)malloc(sizeof(char) * 2 * matrix_size_array_size);
	distribution_threads_model_char = (char*)malloc(sizeof(char) * 2 * distribution_threads_model_array_size);

	computing_start_time_char = (char*)malloc(sizeof(char) * CTIME_ARRAY_SIZE);
	computing_end_time_char = (char*)malloc(sizeof(char) * CTIME_ARRAY_SIZE);

	// convert data to char arrays
	_itoa_s(computing_data.graph_generator_type, graph_generator_type_char, 2 * graph_generator_type_array_size, 10);
	_itoa_s(computing_data.number_of_threads, number_of_threads_char, 2 * number_of_threads_array_size, 10);
	_itoa_s(computing_data.matrix_size, matrix_size_char, 2 * matrix_size_array_size, 10);
	_itoa_s(computing_data.distribution_threads_model, distribution_threads_model_char, 2 * distribution_threads_model_array_size, 10);

	ctime_s(computing_start_time_char, CTIME_ARRAY_SIZE, &computing_data.computing_start_time);
	ctime_s(computing_end_time_char, CTIME_ARRAY_SIZE, &computing_data.computing_end_time);

	// copy data from partial arrays to final array
	memcpy(line_array, graph_generator_type_char, graph_generator_type_array_size);
	offset += graph_generator_type_array_size;

	memcpy(&line_array[offset], SEPARATOR_SIGN, 1);
	offset += 1;

	memcpy(&line_array[offset], number_of_threads_char, number_of_threads_array_size);
	offset += number_of_threads_array_size;

	memcpy(&line_array[offset], SEPARATOR_SIGN, 1);
	offset += 1;

	memcpy(&line_array[offset], matrix_size_char, matrix_size_array_size);
	offset += matrix_size_array_size;

	memcpy(&line_array[offset], SEPARATOR_SIGN, 1);
	offset += 1;

	memcpy(&line_array[offset], distribution_threads_model_char, distribution_threads_model_array_size);
	offset += distribution_threads_model_array_size;

	memcpy(&line_array[offset], SEPARATOR_SIGN, 1);
	offset += 1;

	memcpy(&line_array[offset], computing_start_time_char, CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN);
	offset += CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN;

	memcpy(&line_array[offset], SEPARATOR_SIGN, 1);
	offset += 1;

	memcpy(&line_array[offset], computing_end_time_char, CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN);
	offset += CTIME_ARRAY_SIZE_WITHOUT_EOL_SIGN;

	memcpy(&line_array[offset], "\n\0", 2);
	offset += 2;

	return line_array;
}

char *prepare_table_header()
{
	return "graph_generator_type;number_of_threads;matrix_size;distribution_threads_model;computing_start_time;computing_end_time\n\0";
}

/*
 * Save computing data in csv file
 * */
void save_computing_data(const char *file_path, data_to_save *computing_data, int computing_data_size)
{
	FILE *result_file;
	errno_t err;
	int i;
	char *line_to_write;

	err = fopen_s(&result_file, file_path, "at");
	if (err)
	{
		// TODO error handling
	}

	fputs(prepare_table_header(), result_file);

	for (i = 0; i < computing_data_size; i++)
	{
		printf("%d\n", i);
		line_to_write = prepare_line_to_write(computing_data[i]);
		fputs(line_to_write, result_file);
	}

	fclose(result_file);
}

/*
 * Load configuration from txt file
 * */
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

	fclose(config_file);

	return scenarios;
}
