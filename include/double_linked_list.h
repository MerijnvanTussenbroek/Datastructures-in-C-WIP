#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

/*
Here, we made the following assumptions:
    1 in the list nodes, nodes[0] is the previous node
    2 in the list nodes, nodes[1] is the next node
*/

#define DEFINE_DOUBLE_LINKED_LIST(name, type)       \
DEFINE_GRAPH(name, type);                           \
                                                    \
typedef struct name##_DLL name##_DLL;               \
typedef struct name##_DLL                           \
{                                                   \
    name##_node* head;                              \
    name##_node* tail;                              \
    int length;                                     \
};                                                  \
                                                    \
typedef void (*name##_DLLIterationFunc)(type input);\
                                                    \
name##_DLL* name##_initializeDLL(type newData);     \
void name##_DaddNewNode(name##_DLL* DLL, type newData);\
void name##_DinsertNewNode(name##_DLL* DLL, type newData, int index);\
name##_GraphResult name##_DretrieveData(name##_DLL* DLL, int index);\
void name##_DLLIterate(name##_DLL* DLL, name##_DLLIterationFunc f);\
int name##_DgetSize(name##_DLL* DLL);\
void name##_DremoveItem(name##_DLL* DLL, int index);\
void name##_DchangeValue(name##_DLL* DLL, int index, type newData);\
void name##_DdestroyLinkedList(name##_DLL* DLL);\

