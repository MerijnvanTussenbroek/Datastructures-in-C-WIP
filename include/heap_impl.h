#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "graph_impl.h"

/*This is a max-heap or min-heap depending on the comparison function you give*/
//nodes[0] is left, nodes[1] is right, nodes[2] is the previous node

//the comp function f(a, b) == 1 if a < b
#define DEFINE_HEAP(name, type)     \
DEFINE_GRAPH(name, type);           \
                                    \
name##_heap* name##_initializeHeap(type data, name##_HeapCompFunc f)\
{                                   \
    name##_heap* heap = malloc(sizeof(name##_heap));\
    heap->length = 1;               \
    heap->f = f;                    \
    heap->root = malloc(sizeof(name##_node));\
    heap->root->data = data;        \
    heap->root->length = 3;         \
    heap->root->nodes = malloc(sizeof(name##_node *) * 3);\
    heap->root->nodes[0] = NULL;    \
    heap->root->nodes[1] = NULL;    \
    heap->root->nodes[2] = NULL;    \
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
name##_node* name##_initializeNewNode(type data)\
{                                   \
    name##_node* newNode = malloc(sizeof(name##_node));\
    newNode->data = data;           \
    newNode->length = 3;            \
    newNode->nodes = malloc(sizeof(name##_node *) * 3);\
    newNode->nodes[0] = NULL;       \
    newNode->nodes[1] = NULL;       \
    newNode->nodes[2] = NULL;       \
    return newNode;                 \
}                                   \
                                    \
int name##_addToHeap(name##_HeapCompFunc f, name##_node* current, type value, int* moves, int depth)\
{                                   \
    \
}                                   \
                                    \
int name##_removeFromHeap(name##_HeapCompFunc f, name##_node* current, type value)\
{                                   \
    \
}                                   \
                                    \
int name##_ContainsHeap(name##_HeapCompFunc f, name##_node* current, type value)\
{                                   \
    \
}                                   \
                                    \
void name##_HeapAddNode(name##_HeapCompFunc f, name##_node* origin, name##_node* nodeToBeAdded)\
{                                   \
    \
}                                   \
                                    \
void name##_RestoreHeapBalance(name##_HeapCompFunc f, name##_node* current)\
{                                   \
    \
}                               