#include <stdio.h>
#include <stdlib.h>

int number_of_threads = 0;

void set_number_of_threads(int t_num)
{
	number_of_threads = t_num;
}

void init()
{
	srand(time(NULL));
}