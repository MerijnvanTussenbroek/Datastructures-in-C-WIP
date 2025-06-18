#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define DEFINE_TREE(name, type)     \
DEFINE_GRAPH(name, type);           \
typedef struct name##_tree name##_tree;\
typedef struct name##_tree          \
{                                   \
    name##_node* root;              \
    int amount;                     \
};                                  \
                                    \
name##_tree* name##_initializeTree(type newData);\
void name##_destroyTree(name##_tree* t);\
void name##_addToTree(name##_node* n, int* setOfMoves, int length, int depth, type newData);\
void name##_changeValueInTree(name##_node* n, int* setOfMoves, int length, int depth, type newData);\
void name##_removeFromTree(name##_node* n, int* setOfMoves, int length, int depth, type newData);