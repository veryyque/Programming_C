#include "html.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 5000

void write_html(const char* filename, int** graph, long long num_vertices, 
                long long* distances, long long* prev, long long end_vertex) {
    // Ваш оригинальный код функции без изменений
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "<html>\n<head>\n<title>Dijkstra Algorithm Result</title>\n");
    fprintf(file, "<style>\n");
    fprintf(file, "body {\n");
    fprintf(file, "    font-family: Arial, Helvetica, serif;\n");
    fprintf(file, "    font-style:normal;\n");
    fprintf(file, "    color: rgb(100, 98, 78);\n");
    fprintf(file, "    display: flex;\n");
    fprintf(file, "    justify-content: center;\n");
    fprintf(file, "    align-items: center;\n");
    fprintf(file, "    text-align: center;\n");
    fprintf(file, "    height: 100vh;\n");
    fprintf(file, "    margin: 0;\n");
    fprintf(file, "    position: relative;\n");
    fprintf(file, "    overflow: hidden;\n");
    fprintf(file, "}\n");
    fprintf(file, "body::before {\n");
    fprintf(file, "    content: '';\n");
    fprintf(file, "    position: absolute;\n");
    fprintf(file, "    top: 0;\n");
    fprintf(file, "    left: 0;\n");
    fprintf(file, "    width: 100%%;\n");
    fprintf(file, "    height: 100%%;\n");
    fprintf(file, "    background-image: url('https://i.pinimg.com/736x/df/b5/17/dfb517685df778f97798f1b0e62a821d.jpg');\n");
    fprintf(file, "    background-size: cover;\n");
    fprintf(file, "    background-position: center;\n");
    fprintf(file, "    opacity: 0.7; \n");
    fprintf(file, "}\n");
    fprintf(file, ".container {\n");
    fprintf(file, "    background-color: rgba(253, 255, 218, 0.912);\n");
    fprintf(file, "    padding: 13px;\n");
    fprintf(file, "    border-radius: 15px;\n");
    fprintf(file, "    box-shadow: 10px 10px 5px rgba(82, 93, 120, 0.57);\n");
    fprintf(file, "    color: rgb(139, 132, 93);\n");
    fprintf(file, "    max-width: 800px;\n");
    fprintf(file, "    width: 100%%;\n");
    fprintf(file, "    position: relative;\n");
    fprintf(file, "    z-index: 1;\n");
    fprintf(file, "}\n");
    fprintf(file, "h2 {\n");
    fprintf(file, "    text-align: center;\n");
    fprintf(file, "    font-family: 'Garamond', serif;\n");
    fprintf(file, "    font-size: 35px; \n");
    fprintf(file, "    letter-spacing: 2px; \n");
    fprintf(file, "    color: #fbff00;\n");
    fprintf(file, "    background: #f5e769d1;\n");
    fprintf(file, "    padding: 10px;\n");
    fprintf(file, "    border-radius: 15px;\n");
    fprintf(file, "    color: rgb(97, 96, 94)\n");
    fprintf(file, "}\n");
    fprintf(file, ".table {\n");
    fprintf(file, "    width: 100%%;\n");
    fprintf(file, "    border: none;\n");
    fprintf(file, "    margin-bottom: 20px;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table thead th {\n");
    fprintf(file, "    font-weight: bold;\n");
    fprintf(file, "    text-align: left;\n");
    fprintf(file, "    border: none;\n");
    fprintf(file, "    padding: 10px 15px;\n");
    fprintf(file, "    background: #d8d8d8;\n");
    fprintf(file, "    font-size: 14px;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table thead tr th:first-child {\n");
    fprintf(file, "    border-radius: 8px 0 0 8px;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table thead tr th:last-child {\n");
    fprintf(file, "    border-radius: 0 8px 8px 0;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table tbody td {\n");
    fprintf(file, "    text-align: left;\n");
    fprintf(file, "    border: none;\n");
    fprintf(file, "    padding: 10px 15px;\n");
    fprintf(file, "    font-size: 14px;\n");
    fprintf(file, "    vertical-align: top;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table tbody tr:nth-child(even){\n");
    fprintf(file, "    background: #f3f3f3;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table tbody tr td:first-child {\n");
    fprintf(file, "    border-radius: 8px 0 0 8px;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table tbody tr td:last-child {\n");
    fprintf(file, "    border-radius: 0 8px 8px 0;\n");
    fprintf(file, "}\n");
    fprintf(file, "td[style*=\"background-color: rgb(88, 99, 131)\"] {\n");
    fprintf(file, "    background-color: #95bcd6 !important;\n");
    fprintf(file, "    color: white;\n");
    fprintf(file, "    font-weight: bold;\n");
    fprintf(file, "}\n");
    fprintf(file, ".table tbody tr:hover {\n");
    fprintf(file, "    background-color: rgba(9, 24, 39, 0.309);\n");
    fprintf(file, "}\n");
    fprintf(file, ".table thead th:first-child,\n");
    fprintf(file, ".table tbody td:first-child {\n");
    fprintf(file, "    border-radius: 8px 0 0 8px;\n");
    fprintf(file, "}\n");
    fprintf(file, ".image-left, .image-right {\n");
    fprintf(file, "    width: 150px;\n");
    fprintf(file, "    height: auto; \n");
    fprintf(file, "    opacity: 1; \n");
    fprintf(file, "    position: absolute;\n");
    fprintf(file, "    border: #949637 5px dotted;\n");
    fprintf(file, "}\n");
    fprintf(file, ".image-left {\n");
    fprintf(file, "    left: 90px; \n");
    fprintf(file, "    top: 60px; \n");
    fprintf(file, "}\n");
    fprintf(file, ".image-right {\n");
    fprintf(file, "    right: 90px; \n");
    fprintf(file, "    bottom: 60px;\n");
    fprintf(file, "}\n");
    fprintf(file, "</style>\n");
    fprintf(file, "</head>\n<body>\n");
    fprintf(file, "<!-- Картинка слева -->\n");
    fprintf(file, "<img src=\"https://i.pinimg.com/736x/8b/ee/71/8bee7107e7ada87a42887dec71601569.jpg\" alt=\"Left Image\" class=\"image-left\">\n");
    fprintf(file, "<div class=\"container\">\n");
    fprintf(file, "<h2>ADJACENCY MATRIX</h2>\n");
    fprintf(file, "<table class=\"table\">\n");
    fprintf(file, "<thead>\n");
    fprintf(file, "<tr>\n");
    fprintf(file, "<th></th>\n"); 
    for (long long j = 0; j < num_vertices; j++) {
        fprintf(file, "<th>%lld</th>\n", j + 1); 
    }
    fprintf(file, "</tr>\n");
    fprintf(file, "</thead>\n");
    fprintf(file, "<tbody>\n");

    long long path[MAX_VERTICES];
    long long path_len = 0;
    long long current = end_vertex;
    while (current != -1) {
        path[path_len++] = current;
        current = prev[current];
    }

    int** is_on_path = (int**)malloc(num_vertices * sizeof(int*));
    for (long long i = 0; i < num_vertices; i++) {
        is_on_path[i] = (int*)calloc(num_vertices, sizeof(int));
    }
    for (long long i = 0; i < path_len - 1; i++) {
        long long u = path[i];
        long long v = path[i + 1];
        is_on_path[u][v] = 1;
        is_on_path[v][u] = 1; 
    }

    for (long long i = 0; i < num_vertices; i++) {
        fprintf(file, "<tr>\n");
        fprintf(file, "<th>%lld</th>\n", i + 1); 
        for (long long j = 0; j < num_vertices; j++) {
            if (graph[i][j] != 0 && is_on_path[i][j]) {
                fprintf(file, "<td style=\"background-color: rgba(250, 238, 106, 0.843);\">%d</td>\n", graph[i][j]);
            } else {
                fprintf(file, "<td>%d</td>\n", graph[i][j]);
            }
        }
        fprintf(file, "</tr>\n");
    }
    fprintf(file, "</tbody>\n");
    fprintf(file, "</table>\n");

    fprintf(file, "<h2>VERTEX DISTANCES</h2>\n");
    fprintf(file, "<table class=\"table\">\n");
    fprintf(file, "<thead>\n");
    fprintf(file, "<tr><th>vertex</th><th>distance</th></tr>\n");
    fprintf(file, "</thead>\n");
    fprintf(file, "<tbody>\n");
    for (long long i = 0; i < num_vertices; i++) {
        fprintf(file, "<tr><td>%lld</td><td>%lld</td></tr>\n", i + 1, distances[i]);
    }
    fprintf(file, "</tbody>\n");
    fprintf(file, "</table>\n");

    fprintf(file, "</div>\n");

    fprintf(file, "<!-- Картинка справа -->\n");
    fprintf(file, "<img src=\"https://i.pinimg.com/736x/8b/ee/71/8bee7107e7ada87a42887dec71601569.jpg\" alt=\"Right Image\" class=\"image-right\">\n");
    fprintf(file, "</body>\n</html>\n");

    fclose(file);
    for (long long i = 0; i < num_vertices; i++) {
        free(is_on_path[i]);
    }
    free(is_on_path);
}
