#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffman.h"

typedef struct {
    huffman_node **nodes;
    int size;
    int capacity;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq, int capacity);
void insertnode(PriorityQueue *pq, huffman_node *node);
huffman_node *extractMinnode(PriorityQueue *pq);
void freePriorityQueue(PriorityQueue *pq);

#endif
