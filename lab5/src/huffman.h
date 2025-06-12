#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>

typedef unsigned char byte;

typedef struct huffman_node {
    unsigned long frequency;
    byte symbol;
    struct huffman_node *left;
    struct huffman_node *right;
} huffman_node;

typedef struct {
    int lenght; 
    byte bit_array[8];
} symbol_code;

huffman_node *make_leaf(byte sym, unsigned long frequency);
huffman_node *make_inner_node(huffman_node *left, huffman_node *right);
void destroy_tree(huffman_node *node);
void generate_code_table(const huffman_node *node, symbol_code temp_code, symbol_code code_map[256]);

#endif
