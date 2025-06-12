#include "generate_svg.h"
#include <stdio.h>
#include <math.h>
#define pi 3.14159265358979323846

void generate_svg(Edge* edges, int num_edges, Edge* mst_edges, int mst_size, int num_vertices) {
    FILE* svg_file = fopen("result.svg", "w");
    if (!svg_file) return;

    const int radius = 300;
    const int width = 1920;                  
    const int height = 1080;
    const int center_x = width / 2;         
    const int center_y = height / 2;  

    fprintf(svg_file, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n", width, height);
    fprintf(svg_file, "<image href=\"https://marketplace.canva.com/EAFUFiGX5ek/1/0/1600w/canva-colorful-watercolor-floral-linktree-background-qRHfsd-4Nmc.jpg\" width=\"%d\" height=\"%d\" opacity=\"1\"/>\n", width, height);
    for (int i = 0; i < num_edges; i++) {
        double angle1 = 2 * pi * edges[i].from_vertex / num_vertices;
        double angle2 = 2 * pi * edges[i].to_vertex / num_vertices;
        
        double x1 = center_x + radius * cos(angle1);
        double y1 = center_y + radius * sin(angle1);
        double x2 = center_x + radius * cos(angle2);
        double y2 = center_y + radius * sin(angle2);
        
        fprintf(svg_file, "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" "
                "stroke=\"gray\" stroke-width=\"2\" />\n", x1, y1, x2, y2);
    }
    
    for (int i = 0; i < mst_size; i++) {
        double angle1 = 2 * pi * mst_edges[i].from_vertex / num_vertices;
        double angle2 = 2 * pi * mst_edges[i].to_vertex / num_vertices;
        
        double x1 = center_x + radius * cos(angle1);
        double y1 = center_y + radius * sin(angle1);
        double x2 = center_x + radius * cos(angle2);
        double y2 = center_y + radius * sin(angle2);
        
        fprintf(svg_file, "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" "
                "stroke=\"#FFB6C1\" stroke-width=\"4\" />\n", x1, y1, x2, y2);

    }
    
    
    for (int i = 0; i < num_vertices; i++) {
        double angle = 2 * pi * i / num_vertices;
        double x = center_x + radius * cos(angle);
        double y = center_y + radius * sin(angle);
        
        fprintf(svg_file, "<circle cx=\"%.1f\" cy=\"%.1f\" r=\"5\" fill=\"#FF4E7E\" />\n", x, y);
        fprintf(svg_file, "<text x=\"%.1f\" y=\"%.1f\" font-size=\"40\" text-anchor=\"middle\">%d</text>\n", 
                x, y - 10, i + 1);
    }
    
    fprintf(svg_file, "</svg>");
    fclose(svg_file);
}
