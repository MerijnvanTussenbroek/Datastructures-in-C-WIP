#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int* turnIntoBinary(int num);
int determineNextPos(int* arr1, int* arr2);
int isItPossible(int* arr1, int* arr2);

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
};                                      \
                                        \
typedef struct name##_BTSuccess name##_BUTSuccess;\
typedef struct name##_BTSuccess         \
{                                       \
    int success;                        \
    type value;                         \
};                                      \
                                        \
name##_BT* name##_initializeBT(type initialValue, name##_compFunc f);\
void name##_destroyBT(name##_BT* bt);   \
void name##_addToBT(name##_BT* bt, type value);\
void name##_BTRemoveByIndex(name##_BT* bt, int index);\
void name##_BTRemoveByValue(name##_BT* bt, type value);\
int name##_BTContains(name##_BT* bt, type value);\
name##_GraphResult name##_BTRetrieve(name##_BT* bt, int index);\
void name##_BTCombine(name##_BT* origin, name##_BT* BTToBeAdded);\
void name##_ReorganizeBT(name##_BT* bt);