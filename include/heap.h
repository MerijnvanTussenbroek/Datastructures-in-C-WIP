#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define DEFINE_HEAP(name, type)     \
DEFINE_GRAPH(name, type);           \
typedef int (*name##_HeapCompFunc)(type input1, type input2);\
typedef struct name##_heap name##_heap;\
typedef struct name##_heap          \
{                                   \
    name##_node* root;              \
    int length;                     \
    name##_HeapCompFunc f;          \
    int indexOfNextEmptySlot;       \
};                                  \
                                    \
name##_heap* name##_initializeHeap(type data, name##_HeapCompFunc f);\
void name##_destroyHeap(name##_heap* heap);\
name##_node* name##_initializeNewNode(type data);\
int name##_addToHeap(name##_HeapCompFunc f, name##_node* current, type value, int* moves, int depth);\
int name##_removeFromHeap(name##_HeapCompFunc f, name##_node* current, type value);\
int name##_ContainsHeap(name##_HeapCompFunc f, name##_node* current, type value);\
name##_GraphResult name##_HeapRetrieve(name##_HeapCompFunc f, name##_node* current, int* moves, int depth);\
void name##_HeapAddNode(name##_HeapCompFunc f, name##_node* origin, name##_node* nodeToBeAdded);\
void name##_RestoreHeapBalance(name##_HeapCompFunc f, name##_node* current);