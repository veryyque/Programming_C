#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree {
    int key;
    int height;
    struct avl_tree* left;
    struct avl_tree* right;
} avl_tree;

avl_tree* create_avl_tree(int key);

int get_height(avl_tree* avl_tree);

void update_height(avl_tree* avl_tree);

int get_balance(avl_tree* avl_tree);

avl_tree* rotate_right(avl_tree* y);
avl_tree* rotate_left(avl_tree* x);

avl_tree* insert(avl_tree* avl_tree, int key, int print_rotations);

void order_print(avl_tree* avl_tree);

void PrintPaths(avl_tree* root, char* path, int depth);

void free_tree(avl_tree* avl_tree);
#endif
