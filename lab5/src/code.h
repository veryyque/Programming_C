#ifndef CODEC_H
#define CODEC_H

#include "huffman.h"
#include "bit.h"
#include "priority_queue.h"
#include <stdio.h>

unsigned long frequency_count(FILE *input, unsigned long frequency[256], int skip_header, long offset);
huffman_node *build_huff_tree(unsigned long frequency[256]);
void encode(FILE *input, FILE *output, int skip_header, long offset);
void decode(FILE *input, FILE *output, int skip_header);

#endif
