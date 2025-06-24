#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree_impl.h"

/*This is a max-heap or min-heap depending on the comparison function you give*/
//nodes[0] is left, nodes[1] is right, nodes[2] is the previous node
#define DEFINE_HEAP(name, type)     \
DEFINE_BINARY_TREE(name, type);     \
                                    \
name##_heap* name##_initializeHeap(type data, name##_HeapCompFunc f)\
{                                   \
    name##_heap* heap = malloc(sizeof(name##_heap));\
    heap->length = 1;               \
    heap->f = f;                    \
    heap->root = malloc(sizeof(name##_node));\
    heap->root->data = data;        \
    heap->root->length = 2;         \
    heap->root->nodes = malloc(sizeof(name##_node *) * 2);\
    heap->indexOfNextEmptySlot = 2; \
    return heap;                    \
}                                   \
                                    \
void name##_destroyHeap(name##_heap* heap)\
{                                   \
    name##_destroyGraph(heap->root);\
    free(heap);                     \
}                                   \
                                    \
int name##_addToHeap(name##_heap* heap, type value)\
{                                   \
    \
}                                   \
                                    \
int name##_removeFromHeapIndex(name##_heap*, int index)\
{                                   \
\
}                                   \
                                    \
int name##_removeFromHeapValue(name##_heap* heap, type value)\
{                                   \
\
}                                   \
                                    \
int name##_ContainsHeap(name##_heap* heap, type value)\
{                                   \
\
}                                   \
                                    \
name##_GraphResult name##_HeapRetrieve(name##_heap* heap, int index)\
{                                   \
\
}                                   