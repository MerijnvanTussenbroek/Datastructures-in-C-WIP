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
typedef int (*name##_compFunc)(type inputKey1, type inputKey2);\
                                        \
static inline void name##_removeFromBinTree(name##_node* node, int index, name##_compFunc cmp);\
static inline name##_GraphResult name##_retrieveFromBinTree(name##_node* node, int index, name##_compFunc cmp);\
                                        \
name##_node* name##_initializeBinaryTree(type newData);\
void name##_addToBT(name##_node* node, type newData, name##_compFunc cmp); \
void name##_addNodeToBT(name##_node* origin, name##_node* toBeAdded, name##_compFunc cmp);\
void name##_removeFromBT(name##_node* node, int index, int location, name##_compFunc cmp);\
void name##_reorganiseBT(name##_node* node, name##_compFunc cmp);\
void name##_deleteBT(name##_node* node);\
name##_GraphResult name##_retrieveFromBT(name##_node* node, int index, int location, name##_compFunc cmp);