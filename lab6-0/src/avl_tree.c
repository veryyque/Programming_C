#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

avl_tree* create_avl_tree(int key) {
    avl_tree* node = (avl_tree*)malloc(sizeof(avl_tree));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_height(avl_tree* avl_tree) {
    if (avl_tree == NULL) {
        return 0;
    }
    return avl_tree->height;
}

void update_height(avl_tree* avl_tree) {
    if (avl_tree == NULL) {
        return;
    }
    int left_height = get_height(avl_tree->left);
    int right_height = get_height(avl_tree->right);
    avl_tree->height = (left_height > right_height ? left_height : right_height) + 1;
}

int get_balance(avl_tree* avl_tree) {
    if (avl_tree == NULL) {
        return 0;
    }
    return get_height(avl_tree->left) - get_height(avl_tree->right);
}

avl_tree* rotate_right(avl_tree* y) {
    avl_tree* x = y->left;
    avl_tree* temp = x->right;
    x->right = y;
    y->left = temp;
    update_height(y);
    update_height(x);
    return x;
}

avl_tree* rotate_left(avl_tree* x) {
    avl_tree* y = x->right;
    avl_tree* temp = y->left;
    y->left = x;
    x->right = temp;
    update_height(x);
    update_height(y);
    return y;
}

avl_tree* insert(avl_tree* avl_tree, int key, int print_rotations) {
    if (avl_tree == NULL) {
        return create_avl_tree(key);
    }
    if (key < avl_tree->key) {
        avl_tree->left = insert(avl_tree->left, key, print_rotations);
    } else if (key > avl_tree->key) {
        avl_tree->right = insert(avl_tree->right, key, print_rotations);
    } else {
        return avl_tree;
    }

    update_height(avl_tree);
    int balance_factor = get_balance(avl_tree);

    if (balance_factor > 1 && key < avl_tree->left->key) {
        if (print_rotations) printf("SR ");
        return rotate_right(avl_tree);
    }
    if (balance_factor < -1 && key > avl_tree->right->key) {
        if (print_rotations) printf("SL ");
        return rotate_left(avl_tree);
    }
    if (balance_factor > 1 && key > avl_tree->left->key) {
        if (print_rotations) printf("BR ");
        avl_tree->left = rotate_left(avl_tree->left);
        return rotate_right(avl_tree);
    }
    if (balance_factor < -1 && key < avl_tree->right->key) {
        if (print_rotations) printf("BL ");
        avl_tree->right = rotate_right(avl_tree->right);
        return rotate_left(avl_tree);
    }

    return avl_tree;
}

void order_print(avl_tree* avl_tree) {
    if (avl_tree != NULL) {
        order_print(avl_tree->left);
        printf("%d\n", avl_tree->key);
        order_print(avl_tree->right);
    }
}

void free_tree(avl_tree* avl_tree) {
    if (avl_tree != NULL) {
        free_tree(avl_tree->left);
        free_tree(avl_tree->right);
        free(avl_tree);
    }
}
