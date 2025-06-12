#include "dijkstra.h"
#include <stdlib.h>

static void swap(long long* a, long long* b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

static void init_queue(long long* vertices, long long* distances, long long capacity) {
    for (long long i = 0; i < capacity; i++) {
        vertices[i] = -1;
        distances[i] = INF;
    }
}

static void insert_queue(long long* vertices, long long* distances, long long* size, 
                long long vertex, long long distance) {
    vertices[*size] = vertex;
    distances[*size] = distance;
    (*size)++;
    
    long long i = *size - 1;
    while (i > 0 && distances[(i - 1) / 2] > distances[i]) {
        swap(&vertices[i], &vertices[(i - 1) / 2]);
        swap(&distances[i], &distances[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

static long long extract_min(long long* vertices, long long* distances, long long* size) {
    long long min_vertex = vertices[0];
    (*size)--;
    vertices[0] = vertices[*size];
    distances[0] = distances[*size];

    long long i = 0;
    while (2 * i + 1 < *size) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long smallest = i;

        if (left < *size && distances[left] < distances[smallest]) smallest = left;
        if (right < *size && distances[right] < distances[smallest]) smallest = right;
        if (smallest == i) break;

        swap(&vertices[i], &vertices[smallest]);
        swap(&distances[i], &distances[smallest]);
        i = smallest;
    }

    return min_vertex;
}

static int is_queue_empty(long long size) {
    return size == 0;
}

void dijkstra(int** graph, long long num_vertices, long long start_vertex, 
             long long* distances, long long* prev) {
    long long vertices[MAX_VERTICES];
    long long queue_distances[MAX_VERTICES];
    long long queue_size = 0;

    init_queue(vertices, queue_distances, MAX_VERTICES);

    for (long long i = 0; i < num_vertices; i++) {
        distances[i] = INF;
        prev[i] = -1;
    }
    distances[start_vertex] = 0;
    insert_queue(vertices, queue_distances, &queue_size, start_vertex, 0);

    while (!is_queue_empty(queue_size)) {
        long long current_vertex = extract_min(vertices, queue_distances, &queue_size);
        
        for (long long neighbor = 0; neighbor < num_vertices; neighbor++) {
            if (graph[current_vertex][neighbor] != 0) {
                long long edge_weight = graph[current_vertex][neighbor];
                long long new_distance = distances[current_vertex];
                
                if (new_distance != INF) {
                    new_distance += edge_weight;
                    if (new_distance < distances[neighbor]) {
                        distances[neighbor] = new_distance;
                        prev[neighbor] = current_vertex;
                        insert_queue(vertices, queue_distances, &queue_size, neighbor, new_distance);
                    }
                }
            }
        }
    }
}
