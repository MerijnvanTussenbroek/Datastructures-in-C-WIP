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
name##_node* name##_initializeDLL(type newData);     \
void name##_DaddNewNode(name##_node* list, type newData);\
void name##_DinsertNewNode(name##_node** list, type newData, int index);\
name##_GraphResult name##_DretrieveData(name##_node * list, int index);\
int name##_DgetSize(name##_node * list);\
void name##_DremoveItem(name##_node** list, int index);\
void name##_DchangeValue(name##_node* list, int index, type newData);\
void name##_DdestroyLinkedList(name##_node* list);\

