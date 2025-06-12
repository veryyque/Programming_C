#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"
#include "html.h"

void free_graph(int** graph, int N) {
    if (graph) {
        for (int i = 0; i < N; i++) {
            if (graph[i]) free(graph[i]);
        }
        free(graph);
    }
}

void print_results(int** graph, long long num_vertices, long long* distances, 
                  long long* prev, long long end_vertex) {
    for (long long i = 0; i < num_vertices; i++) {
        if (distances[i] == INF) printf("oo ");
        else if (distances[i] > INT_MAX) printf("INT_MAX+ ");
        else printf("%lld ", distances[i]);
    }
    printf("\n");

    if (distances[end_vertex] == INF) {
        printf("no path\n");
    } else {
        long long path[MAX_VERTICES];
        long long path_len = 0;
        long long current = end_vertex;
        while (current != -1) {
            path[path_len++] = current + 1;
            current = prev[current];
        }
        
        if (distances[end_vertex] > INT_MAX) {
            long long path_count = 0;
            long long on_path[MAX_VERTICES] = {0};
            for (long long i = 0; i < path_len; i++) {
                on_path[path[i] - 1] = 1;
            }
            for (long long i = 0; i < num_vertices; i++) {
                if (!on_path[i] && distances[i] != INF && graph[i][end_vertex] != 0) {
                    long long alt_distance = distances[i] + graph[i][end_vertex];
                    if (alt_distance <= distances[end_vertex]) path_count++;
                }
            }
            if (path_count >= 1) {
                printf("overflow\n");
            } else {
                for (long long i = 0; i < path_len; i++) {
                    printf("%lld ", path[i]);
                }
                printf("\n");
            }
        } else {
            for (long long i = 0; i < path_len; i++) {
                printf("%lld ", path[i]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char* argv[]) {
    const char* output_filename = NULL;
    if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        output_filename = argv[2];
    } else if (argc != 1) {
        printf("Usage: %s [-p FILENAME]\n", argv[0]);
        return 1;
    }

    long long num_vertices, start_vertex, end_vertex, num_edges;
    if (scanf("%lld", &num_vertices) != 1) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (num_vertices < 0 || num_vertices > MAX_VERTICES) {
        printf("bad number of vertices\n");
        return 0;
    }

    if (scanf("%lld %lld", &start_vertex, &end_vertex) != 2) {
        printf("bad vertex\n");
        return 0;
    }
    start_vertex--; end_vertex--;
    if (start_vertex < 0 || start_vertex >= num_vertices || 
        end_vertex < 0 || end_vertex >= num_vertices) {
        printf("bad vertex\n");
        return 0;
    }

    if (scanf("%lld", &num_edges) != 1) {
        printf("bad number of edges\n");
        return 0;
    }
    if (num_edges < 0 || num_edges > num_vertices * (num_vertices - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    int** graph = (int**)malloc(num_vertices * sizeof(int*));
    if (!graph) return 1;
    for (long long i = 0; i < num_vertices; i++) {
        graph[i] = (int*)calloc(num_vertices, sizeof(int));
        if (!graph[i]) {
            free_graph(graph, num_vertices);
            return 1;
        }
    }

    for (long long i = 0; i < num_edges; i++) {
        long long from_vertex, to_vertex, edge_weight;
        if (scanf("%lld %lld %lld", &from_vertex, &to_vertex, &edge_weight) != 3) {
            printf("bad edge\n");
            free_graph(graph, num_vertices);
            return 0;
        }
        from_vertex--; to_vertex--;
        if (from_vertex < 0 || from_vertex >= num_vertices || 
            to_vertex < 0 || to_vertex >= num_vertices) {
            printf("bad vertex\n");
            free_graph(graph, num_vertices);
            return 0;
        }
        if (edge_weight < 0 || edge_weight > INT_MAX) {
            printf("bad length\n");
            free_graph(graph, num_vertices);
            return 0;
        }
        graph[from_vertex][to_vertex] = (int)edge_weight;
        graph[to_vertex][from_vertex] = (int)edge_weight;
    }
    long long* distances = (long long*)malloc(num_vertices * sizeof(long long));
    long long* prev = (long long*)malloc(num_vertices * sizeof(long long));
    dijkstra(graph, num_vertices, start_vertex, distances, prev);
    if (output_filename) {
        write_html(output_filename, graph, num_vertices, distances, prev, end_vertex);
    } else {
        print_results(graph, num_vertices, distances, prev, end_vertex);
    }
    free_graph(graph, num_vertices);
    free(distances);
    free(prev);

    return 0;
}
