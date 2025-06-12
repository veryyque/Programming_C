#include "avl_tree.h"
#include <stdio.h>
#include <string.h>

void PrintPaths(avl_tree* root, char* path, int depth) {
    if (root == NULL) {
        return;
    }
    
    if (root->left == NULL && root->right == NULL) {
        path[depth] = '\0'; 
        printf("%s %d\n", path, root->key);
        return;
    }

    if (root->left != NULL) {
        path[depth] = 'L';
        PrintPaths(root->left, path, depth + 1);
    }

    if (root->right != NULL) {
        path[depth] = 'R';
        PrintPaths(root->right, path, depth + 1);
    }
}
