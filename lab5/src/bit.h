#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdio.h>
#include "huffman.h"

typedef struct {
    FILE *out;
    byte current;
    int bit_position;
} bit_write;

typedef struct {
    FILE *in;
    byte current;
    int bit_position;
} bit_read;

void init_bit_write(bit_write *bw, FILE *out);
void WriteBit(bit_write *bw, int bit_value);
void WriteBits(bit_write *bw, byte sym);
void flush_bit_write(bit_write *bw);
void serializeTree(const huffman_node *node, bit_write *bw);

void init_bit_read(bit_read *br, FILE *in);
int ReadBit(bit_read *br);
byte ReadBits(bit_read *br);
huffman_node *deserializeTree(bit_read *br);

#endif
