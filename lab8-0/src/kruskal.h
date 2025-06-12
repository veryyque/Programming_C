#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <limits.h>

#define INF INT_MAX
#define MAX_VERTICES 5000

typedef struct {
    short from_vertex;
    short to_vertex;
    int edge_weight;
} Edge;

extern int dsu_parent[MAX_VERTICES];
extern short dsu_rank[MAX_VERTICES];

void dsu_init(int num_vertices);
int dsu_find(int i);
void dsu_union(int x, int y);
int compare_edges(const void* a, const void* b);
int is_graph_connected(Edge* edges, int num_edges, int num_vertices);
void kruskal_algorithm(Edge* edges, int num_edges, int num_vertices, int generate_graph);

#endif
