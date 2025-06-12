#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>

#define MAX_VERTICES 5000
#define INF LLONG_MAX

void dijkstra(int** graph, long long num_vertices, long long start_vertex, 
             long long* distances, long long* prev);

#endif
