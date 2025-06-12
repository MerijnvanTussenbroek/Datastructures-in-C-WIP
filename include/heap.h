#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

#define DEFINE_HEAP(name, type)     \
DEFINE_BINARY_TREE(name, type);     \
typedef struct name##_heap name##_heap;\
typedef struct name##_heap          \
{                                   \
    name##_node* BinaryTree;        \
};                                  \
                                    \
typedef struct name##_heapSuccess name##_heapSuccess;\
typedef struct name##_heapSuccess   \
{                                   \
    int success;                    \
    type result;                    \
};