#include "huffman.h"
#include "bit.h"
#include "priority_queue.h"
#include <stdio.h>
#include <string.h>

unsigned long frequency_count(FILE *input, unsigned long frequency[256], int skip_header, long offset)
{
    byte sym;
    unsigned long total_size = 0;
    fseek(input, skip_header ? offset : 0, SEEK_SET);
    while (fread(&sym, 1, 1, input) == 1)
    {
        frequency[sym]++;
        total_size++;
    }
    return total_size;
}

huffman_node *build_huff_tree(unsigned long frequency[256])
{
    PriorityQueue pq;
    initPriorityQueue(&pq, 256);
    for (int i = 0; i < 256; ++i)
    {
        if (frequency[i] > 0)
        {
            huffman_node *node = make_leaf((byte)i, frequency[i]);
            if (node)
                insertnode(&pq, node);
        }
    }
    while (pq.size > 1)
    {
        huffman_node *left_node = extractMinnode(&pq);
        huffman_node *right_node = extractMinnode(&pq);
        if (left_node && right_node)
        {
            huffman_node *parent = make_inner_node(left_node, right_node);
            if (parent)
                insertnode(&pq, parent);
        }
    }
    huffman_node *root = extractMinnode(&pq);
    freePriorityQueue(&pq);
    return root;
}

void encode(FILE *input, FILE *output, int skip_header, long offset)
{
    unsigned long frequency[256] = {0};
    unsigned long input_size = frequency_count(input, frequency, skip_header, offset);
    if (input_size == 0)
    {
        uint32_t zero_size = 0;
        fwrite(&zero_size, sizeof(uint32_t), 1, output);
        return;
    }

    huffman_node *root_node = build_huff_tree(frequency);
    if (!root_node)
        return;

    uint32_t size = (uint32_t)input_size;
    fwrite(&size, sizeof(uint32_t), 1, output);

    bit_write bw;
    init_bit_write(&bw, output);
    serializeTree(root_node, &bw);

    symbol_code code_map[256] = {{0}};
    symbol_code empty_code = {0};
    generate_code_table(root_node, empty_code, code_map);

    fseek(input, skip_header ? offset : 0, SEEK_SET);
    byte sym;
    while (fread(&sym, 1, 1, input) == 1)
    {
        symbol_code code = code_map[sym];
        for (int i = 0; i < code.lenght; ++i)
        {
            int byte_idx = i / 8;
            int bit_pos = i % 8;
            int bit = (code.bit_array[byte_idx] >> (7 - bit_pos)) & 1;
            WriteBit(&bw, bit);
        }
    }
    flush_bit_write(&bw);
    destroy_tree(root_node);
}

void decode(FILE *input, FILE *output, int skip_header)
{
    fseek(input, skip_header ? 1 : 0, SEEK_SET);
    uint32_t data_length;
    if (fread(&data_length, sizeof(uint32_t), 1, input) != 1)
        return;
    if (data_length == 0)
        return;

    bit_read br;
    init_bit_read(&br, input);
    huffman_node *root_node = deserializeTree(&br);
    if (!root_node)
    {
        printf("Ошибка: некорректное дерево в данных\n");
        return;
    }

    if (!root_node->left && !root_node->right)
    {
        byte sym = root_node->symbol;
        for (uint32_t i = 0; i < data_length; ++i)
        {
            fwrite(&sym, 1, 1, output);
        }
    }
    else
    {
        uint32_t decoded_frequency = 0;
        huffman_node *current_node = root_node;
        while (decoded_frequency < data_length)
        {
            int bit = ReadBit(&br);
            if (bit == -1)
            {
                printf("Ошибка: неожиданный конец файла\n");
                break;
            }
            current_node = bit ? current_node->right : current_node->left;
            if (!current_node)
            {
                printf("Ошибка: неверный код Хаффмана\n");
                break;
            }
            if (!current_node->left && !current_node->right)
            {
                fwrite(&current_node->symbol, 1, 1, output);
                decoded_frequency++;
                current_node = root_node;
            }
        }
        if (decoded_frequency != data_length)
        {
            printf("Декодировано %u символов, ожидалось %u\n", decoded_frequency, data_length);
        }
    }
    destroy_tree(root_node);
}
