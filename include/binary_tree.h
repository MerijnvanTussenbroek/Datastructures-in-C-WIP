#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


#define DEFINE_BINARY_TREE(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
typedef int (*name##_compFunc)(type input1, type input2);\
                                        \
typedef struct name##_BT name##_BT;     \
typedef struct name##_BT                \
{                                       \
    name##_node* root;                  \
    int length;                         \
    name##_compFunc f;                  \
    int count;                          \
};                                      \
                                        \
name##_BT* name##_initializeBT(type initialValue, name##_compFunc f);\
void name##_destroyBT(name##_BT* bt);   \
void name##_addToBT(name##_compFunc f, name##_node* current, type value);\
void name##_BTRemoveByValue(name##_compFunc f, name##_node* current, type value);\
int name##_BTContainsfunc(name##_compFunc f, name##_node* current, type value);\
void name##_BTCombine(name##_compFunc f, name##_node* origin, name##_node* BTToBeAdded);\
void name##_ReorganizeBT(name##_BT* bt);