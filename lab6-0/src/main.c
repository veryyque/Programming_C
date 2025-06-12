#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int vertex_count;
    if (scanf("%d", &vertex_count) != 1) {
        printf("Empty input\n");
        return 0;
    }
    if (vertex_count < 0 || vertex_count > 2000000) {
        printf("Bad input\n");
        return 0;
    }
    if (vertex_count == 0) {
        printf("0\n");
        return 0;
    }

    avl_tree* root = NULL;
    int key;
    int input_count = 0;

    while (input_count < vertex_count && scanf("%d", &key) == 1) {
        root = insert(root, key, vertex_count < 100);
        input_count++;
    }

    if (input_count != vertex_count) {
        printf("Bad input\n");
        free_tree(root);
        return 0;
    }

    printf("%d\n", get_height(root));

    if (argc > 1) {
        if (strcmp(argv[1], "-t") == 0) {
            order_print(root); 
        } else if (strcmp(argv[1], "tree") == 0) {
            char path[2000000];
            PrintPaths(root, path, 0);
        }
    }

    free_tree(root);
    return 0;
}
