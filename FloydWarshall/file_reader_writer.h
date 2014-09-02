#ifndef _FILE_READER_WRITER_
#define _FILE_READER_WRITER_

/*
 * distribution_threads_model
 * 0 - all threads for all matrix iteration
 * 1 - sqrt(number_of_thread) for i - iteration and j - iteration
 * * i * j - all threads
 * */

/*
 * Config file structure (*.txt file)
 * graph_generator_type matrix_size number_of_threads distribution_threads_model
 * */

/*
 * Result file structure (*.csv file) 
 * graph_generator_type,matrix_size,number_of_threads,distribution_threads_model,computing_start_time,computing_end_time
 * */

typedef struct {
	int graph_generator_type;
	int number_of_threads;
	int matrix_size;
	int distribution_threads_model;
	time_t computing_start_time;
	time_t computing_end_time;
} data_to_save;

typedef struct {
	int graph_generator_type; // 0 - SMALL / 1 - HUGE
	int matrix_size;
	int number_of_threads;
	int distribution_threads_model;
} configuration_data;

void save_computing_data(const char *file_path, data_to_save *computing_data);
configuration_data *load_configuration_data(const char *file_path, int number_of_scenarios);

#endif _FILE_READER_WRITER_