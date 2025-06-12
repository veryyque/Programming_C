#include "kruskal.h"
#include "generate_svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dsu_parent[MAX_VERTICES];
short dsu_rank[MAX_VERTICES];

void dsu_init(int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        dsu_parent[i] = i;
        dsu_rank[i] = 0;
    }
}

int dsu_find(int i) {
    if (dsu_parent[i] != i) {
        dsu_parent[i] = dsu_find(dsu_parent[i]);
    }
    return dsu_parent[i];
}

void dsu_union(int x, int y) {
    int xroot = dsu_find(x);
    int yroot = dsu_find(y);
    
    if (xroot == yroot) return;
    
    if (dsu_rank[xroot] < dsu_rank[yroot]) {
        dsu_parent[xroot] = yroot;
    } else {
        dsu_parent[yroot] = xroot;
        if (dsu_rank[xroot] == dsu_rank[yroot]) {
            dsu_rank[xroot]++;
        }
    }
}

int compare_edges(const void* a, const void* b) {
    const Edge* edgeA = (const Edge*)a;
    const Edge* edgeB = (const Edge*)b;
    
    if (edgeA->edge_weight > edgeB->edge_weight) return 1;
    if (edgeA->edge_weight < edgeB->edge_weight) return -1;
    
    if (edgeA->from_vertex > edgeB->from_vertex) return 1;
    if (edgeA->from_vertex < edgeB->from_vertex) return -1;
    
    if (edgeA->to_vertex > edgeB->to_vertex) return 1;
    if (edgeA->to_vertex < edgeB->to_vertex) return -1;
    
    return 0;
}

int is_graph_connected(Edge* edges, int num_edges, int num_vertices) {
    if (num_vertices == 0) return 0;
    
    dsu_init(num_vertices);
    
    for (int i = 0; i < num_edges; i++) {
        dsu_union(edges[i].from_vertex, edges[i].to_vertex);
    }
    
    int root = dsu_find(0);
    for (int i = 1; i < num_vertices; i++) {
        if (dsu_find(i) != root) return 0;
    }
    return 1;
}

void kruskal_algorithm(Edge* edges, int num_edges, int num_vertices, int generate_graph) {
    if (num_vertices == 0 || !is_graph_connected(edges, num_edges, num_vertices)) {
        printf("no spanning tree\n");
        return;
    }
    
    qsort(edges, num_edges, sizeof(Edge), compare_edges);
    
    dsu_init(num_vertices);
    Edge* mst_edges = (Edge*)malloc((num_vertices - 1) * sizeof(Edge));
    if (mst_edges == NULL) return;
    int mst_size = 0;
    
    for (int i = 0; i < num_edges && mst_size < num_vertices - 1; i++) {
        int from_root = dsu_find(edges[i].from_vertex);
        int to_root = dsu_find(edges[i].to_vertex);
        
        if (from_root != to_root) {
            mst_edges[mst_size] = edges[i];
            mst_size++;
            dsu_union(from_root, to_root);
        }
    }
    
    for (int i = 0; i < mst_size; i++) {
        for (int j = i + 1; j < mst_size; j++) {
            if (mst_edges[i].from_vertex > mst_edges[j].from_vertex) {
                Edge temp = mst_edges[i];
                mst_edges[i] = mst_edges[j];
                mst_edges[j] = temp;
            } else if (mst_edges[i].from_vertex == mst_edges[j].from_vertex) {
                if (mst_edges[i].to_vertex > mst_edges[j].to_vertex) {
                    Edge temp = mst_edges[i];
                    mst_edges[i] = mst_edges[j];
                    mst_edges[j] = temp;
                }
            }
        }
    }
    
    for (int i = 0; i < mst_size; i++) {
        printf("%d %d\n", mst_edges[i].from_vertex + 1, mst_edges[i].to_vertex + 1);
    }
    
    if (generate_graph) {
        generate_svg(edges, num_edges, mst_edges, mst_size, num_vertices);
    }
    
    free(mst_edges);
}
