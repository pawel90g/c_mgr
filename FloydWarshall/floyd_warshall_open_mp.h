#ifndef _FLOYD_WARSHALL_OPEN_MP_
#define _FLOYD_WARSHALL_OPEN_MP_

typedef enum
{
	STEADY = 0,
	MAX = 1,
} t_thread_distribution_model;

void floyd_warshall(double **graph, long graph_size, t_thread_distribution_model t_distrib);

#endif _FLOYD_WARSHALL_OPEN_MP_