#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "set.h"

#define DEFINE_GRAPH(name, type)        \
typedef struct name##_node name##_node; \
typedef struct name##_node              \
{                                       \
    type data;                          \
    name##_node** nodes;                \
    int length;                         \
};                                      \
                                        \
typedef struct                          \
{                                       \
    int success;                        \
    type value;                         \
} name##_GraphResult;                   \
                                        \
DEFINE_SET(name##_node* , name);        \
name##_node* name##_initializeGraph(type newData);\
void name##_addNewNode(name##_node* node, type newData);\
void name##_removeNode(name##_node* node, int index);\
name##_node* name##_createNewNode(type value);\
void name##_addExistingNode(name##_node* origin, name##_node* nodeToBeAdded);\
void name##_destroyGraph(name##_node* node);\
int name##_cmpFunc(name##_node* node1, name##_node* node2);\
void name##_CollectAllNodes(name##_node* node, name##_set* s);

