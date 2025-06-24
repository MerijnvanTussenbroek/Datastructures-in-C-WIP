#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

#define DEFINE_HEAP(name, type)     \
DEFINE_BINARY_TREE(name, type);     \
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
int name##_addToHeap(name##_heap* heap, type value);\
int name##_removeFromHeapIndex(name##_heap*, int index);\
int name##_removeFromHeapValue(name##_heap* heap, type value);\
int name##_ContainsHeap(name##_heap* heap, type value);\
name##_GraphResult name##_HeapRetrieve(name##_heap* heap, int index);