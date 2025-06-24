#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

/*
Here, we make the assumption that nodes[0] is the next node in the list
*/

#define DEFINE_LINKED_LIST(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
typedef struct name##_LL name##_LL;     \
typedef struct name##_LL                \
{                                       \
    name##_node* list;                  \
    int totalLength;                    \
};                                      \
                                        \
typedef void (*name##_LLIterationFunc)(type input);\
                                        \
name##_LL* name##_initializeLinkedList(type newData);\
name##_node* name##_initializeNode(type newData);\
void name##_addNewNodeToLL(name##_LL* LL, type newData);\
void name##_insertNewNodeToLL(name##_LL* LL, type newData, int index);\
name##_GraphResult name##_retrieveDataFromLL(name##_LL* LL, int index);\
void name##_iterateOverLL(name##_LL* LL, name##_LLIterationFunc f);\
int name##_getSizeFromLL(name##_LL* LL);\
void name##_removeItemFromLL(name##_LL* LL, int index);\
void name##_changeValueinLL(name##_LL* LL, int index, type newData);\
void name##_destroyLinkedList(name##_LL* LL);

