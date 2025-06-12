#include "huffman.h"
#include <stdlib.h>

huffman_node *make_leaf(byte sym, unsigned long frequency)
{
    huffman_node *node = (huffman_node *)calloc(1, sizeof(huffman_node));
    if (!node)
        return NULL;
    node->frequency = frequency;
    node->symbol = sym;
    node->left = NULL;
    node->right = NULL;
    return node;
}

huffman_node *make_inner_node(huffman_node *left, huffman_node *right)
{
    huffman_node *node = (huffman_node *)calloc(1, sizeof(huffman_node));
    if (!node)
        return NULL;
    node->frequency = left->frequency + right->frequency;
    node->left = left;
    node->right = right;
    return node;
}
void add_bit(symbol_code *code, int bit_value)
{
    if (code->lenght >= 64)
        return; 
    int byte_idx = code->lenght / 8;
    int bit_idx = code->lenght % 8;
    if (bit_idx == 0)
        code->bit_array[byte_idx] = 0;
    if (bit_value)
        code->bit_array[byte_idx] |= (1 << (7 - bit_idx));
    code->lenght++;
}
void destroy_tree(huffman_node *node)
{
    if (node)
    {
        destroy_tree(node->left);
        destroy_tree(node->right);
        free(node);
    }
}

void generate_code_table(const huffman_node *node, symbol_code temp_code, symbol_code code_map[256])
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        code_map[node->symbol] = temp_code;
    }
    else
    {
        symbol_code code_left = temp_code;
        add_bit(&code_left, 0);
        generate_code_table(node->left, code_left, code_map);
        symbol_code code_right = temp_code;
        add_bit(&code_right, 1);
        generate_code_table(node->right, code_right, code_map);
    }
}
