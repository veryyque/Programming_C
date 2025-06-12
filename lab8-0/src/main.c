#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int generate_graph = 0;
    if (argc > 1 && strcmp(argv[1], "-g") == 0) {
        generate_graph = 1;
    }
    
    int num_vertices, num_edges;
    
    if (scanf("%d", &num_vertices) != 1) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (num_vertices < 0 || num_vertices > MAX_VERTICES) {
        printf("bad number of vertices\n");
        return 0;
    }

    if (scanf("%d", &num_edges) != 1) {
        printf("bad number of edges\n");
        return 0;
    }
    if (num_edges < 0 || num_edges > num_vertices * (num_vertices - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    Edge* edges = (Edge*)malloc(num_edges * sizeof(Edge));
    if (edges == NULL) return 0;

    for (int i = 0; i < num_edges; i++) {
        int from_vertex, to_vertex, edge_weight;
        if (scanf("%d %d %d", &from_vertex, &to_vertex, &edge_weight) != 3) {
            printf("bad number of lines\n");
            free(edges);
            return 0;
        }
        
        if (from_vertex < 1 || from_vertex > num_vertices || 
            to_vertex < 1 || to_vertex > num_vertices) {
            printf("bad vertex\n");
            free(edges);
            return 0;
        }
        
        if (edge_weight < 0 || edge_weight > INF) {
            printf("bad length\n");
            free(edges);
            return 0;
        }
        
        edges[i].from_vertex = (short)(from_vertex - 1);
        edges[i].to_vertex = (short)(to_vertex - 1);
        edges[i].edge_weight = edge_weight;
    }

    kruskal_algorithm(edges, num_edges, num_vertices, generate_graph);
    free(edges);
    
    return 0;
}
