#include "priority_queue.h"
#include <stdlib.h>

void initPriorityQueue(PriorityQueue *pq, int capacity)
{
    pq->nodes = (huffman_node **)malloc(sizeof(huffman_node *) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
}

void swap_nodes(huffman_node **a, huffman_node **b)
{
    huffman_node *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue *pq, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < pq->size && pq->nodes[left]->frequency < pq->nodes[smallest]->frequency)
        smallest = left;
    if (right < pq->size && pq->nodes[right]->frequency < pq->nodes[smallest]->frequency)
        smallest = right;
    if (smallest != idx)
    {
        swap_nodes(&pq->nodes[idx], &pq->nodes[smallest]);
        heapify(pq, smallest);
    }
}

void insertnode(PriorityQueue *pq, huffman_node *node)
{
    if (pq->size == pq->capacity)
        return;
    pq->nodes[pq->size] = node;
    int idx = pq->size++;
    while (idx > 0 && pq->nodes[(idx - 1) / 2]->frequency > pq->nodes[idx]->frequency)
    {
        swap_nodes(&pq->nodes[idx], &pq->nodes[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

huffman_node *extractMinnode(PriorityQueue *pq)
{
    if (pq->size == 0)
        return NULL;
    huffman_node *min_node = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    heapify(pq, 0);
    return min_node;
}

void freePriorityQueue(PriorityQueue *pq)
{
    free(pq->nodes);
    pq->nodes = NULL;
    pq->size = 0;
    pq->capacity = 0;
}
