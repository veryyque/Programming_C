#ifndef WRITE_HTML_H
#define WRITE_HTML_H

void write_html(const char* filename, int** graph, long long num_vertices, 
                long long* distances, long long* prev, long long end_vertex);

#endif
