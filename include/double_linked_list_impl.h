#pragma once

#include "graph_impl.h"

#define DEFINE_DOUBLE_LINKED_LIST(name, type)       \
DEFINE_GRAPH(name, type);                           \
name##_node* name##_initializeDLL(type newData)     \
{                                                   \
    name##_node* list = malloc(sizeof(name##_node));\
    list->nodes = malloc(sizeof(name##_node *) * 2);\
    list->nodes[0] = NULL;                          \
    list->nodes[1] = NULL;                          \
    list->data = newData;                           \
    list->length = 2;                               \
    return list;                                    \
}                                                   \
                                                    \
void name##_DaddNewNode(name##_node* list, type newData)\
{                                                   \
    name##_node* nodeToBeAdded = name##_initializeDLL(newData);\
    name##_node* current = list;                    \
    while(current->nodes[1] != NULL)                \
    {                                               \
        current = current->nodes[1];                \
    }                                               \
    current->nodes[1] = nodeToBeAdded;              \
    nodeToBeAdded->nodes[0] = current;              \
}                                                   \
                                                    \
void name##_DinsertNewNode(name##_node** list, type newData, int index)\
{                                                   \
    if(index == 0)                                  \
    {                                               \
        name##_node* newNode = name##_initializeDLL(newData);\
        newNode->nodes[1] = (*list);                \
        (*list)->nodes[0] = newNode;                \
        *list = newNode;                            \
        return;                                     \
    }                                               \
    name##_node* current = *list;                   \
    while(index > 1)                                \
    {                                               \
        if(current->nodes[1] == NULL)               \
        {                                           \
            printf("Tried inserting past end of list");\
            return;                                 \
        }                                           \
        index--;                                    \
        current = current->nodes[1];                \
    }                                               \
    name##_node* nodeToBeAdded = name##_initializeDLL(newData);\
    name##_node* nodeToBeConnected = current->nodes[1];\
                                                    \
    current->nodes[1] = nodeToBeAdded;              \
    nodeToBeConnected->nodes[0] = nodeToBeAdded;    \
    nodeToBeAdded->nodes[0] = current;              \
    nodeToBeAdded->nodes[1] = nodeToBeConnected;    \
}                                                   \
                                                    \
name##_GraphResult name##_DretrieveData(name##_node* list, int index)\
{                                                   \
    name##_GraphResult result = { 0 };              \
    name##_node* current = list;                    \
    while(index > 0)                                \
    {                                               \
        if(current->nodes[1] == NULL)               \
        {                                           \
            printf("Tried retrieving from node that doesn't exist");\
            return result;                          \
        }                                           \
        index--;                                    \
        current = current->nodes[1];                \
    }                                               \
                                                    \
    result.success = 1;                             \
    result.value = current->data;                   \
    return result;                                  \
}                                                   \
                                                    \
int name##_DgetSize(name##_node * list)             \
{                                                   \
    int length = 1;                                 \
    name##_node* current = list;                    \
    while(current->nodes[1] != NULL)                \
    {                                               \
        length++;                                   \
        current = current->nodes[1];                \
    }                                               \
    return length;                                  \
}                                                   \
                                                    \
void name##_DremoveItem(name##_node** list, int index)\
{                                                   \
    if(index == 0)                                  \
    {                                               \
        name##_node* nodeToBeConnected = (*list)->nodes[1];\
        if(nodeToBeConnected == NULL)               \
        {                                           \
            printf("Tried removing a non-existing node");\
            return;                                 \
        }                                           \
        name##_node* nodeToBeRemoved = *list;       \
        *list = nodeToBeConnected;                  \
        nodeToBeRemoved->nodes[0] = NULL;           \
        nodeToBeRemoved->nodes[1] = NULL;           \
        name##_DdestroyLinkedList(nodeToBeRemoved);  \
        return;                                     \
    }                                               \
                                                    \
    name##_node* current = *list;                   \
    while(index > 1)                                \
    {                                               \
        if(current->nodes[1] == NULL)               \
        {                                           \
            printf("Tried removing a non-existing node");\
            return;                                 \
        }                                           \
        current = current->nodes[1];                \
        index--;                                    \
    }                                               \
    name##_node* nodeToBeRemoved = current->nodes[1];\
    name##_node* nodeToBeConnected = nodeToBeRemoved->nodes[1];\
    current->nodes[1] = nodeToBeConnected;          \
    nodeToBeConnected->nodes[0] = current;          \
    nodeToBeRemoved->nodes[0] = NULL;               \
    nodeToBeRemoved->nodes[1] = NULL;               \
    name##_DdestroyLinkedList(nodeToBeRemoved);      \
}                                                   \
                                                    \
void name##_DchangeValue(name##_node* list, int index, type newData)\
{                                                   \
    name##_node* current = list;                    \
    while(index > 0)                                \
    {                                               \
        if(current->nodes[1] == NULL)               \
        {                                           \
            printf("Tried changing value of non-existant node");\
            return;                                 \
        }                                           \
        current = current->nodes[1];                \
        index--;                                    \
    }                                               \
    current->data = newData;                        \
}                                                   \
                                                    \
void name##_DdestroyLinkedList(name##_node* list)   \
{                                                   \
    name##_destroyGraph(list);                      \
}