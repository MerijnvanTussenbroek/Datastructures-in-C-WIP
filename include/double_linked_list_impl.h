#pragma once

#include "graph_impl.h"
/*
When we add a new node, we essentially create a new head

a <-> b <-> c <-> d

if we add node x, it becomes

x <-> a <-> b <-> c <-> d
*/

#define DEFINE_DOUBLE_LINKED_LIST(name, type)       \
DEFINE_GRAPH(name, type);                           \
name##_DLL* name##_initializeDLL(type newData)      \
{                                                   \
    name##_DLL* DLL = malloc(sizeof(name##_DLL));   \
    DLL->head = malloc(sizeof(name##_node));        \
    DLL->tail = DLL->head;                          \
    DLL->head->data = newData;                      \
    DLL->head->length = 2;                          \
    DLL->head->nodes = malloc(sizeof(name##_node *) * 2);\
    DLL->head->nodes[0] = NULL;                     \
    DLL->head->nodes[1] = NULL;                     \
    DLL->length = 1;                                \
    return DLL;                                     \
}                                                   \
                                                    \
void name##_DaddNewNode(name##_DLL* DLL, type newData)\
{                                                   \
    name##_node* previousHead = DLL->head;          \
    name##_node* newNode = malloc(sizeof(name##_node));\
    newNode->data = newData;                        \
    newNode->nodes = malloc(sizeof(name##_node *) * 2);\
    newNode->nodes[0] = NULL;                       \
    newNode->nodes[1] = previousHead;               \
    previousHead->nodes[0] = newNode;               \
    DLL->head = newNode;                            \
    DLL->length++;                                  \
}                                                   \
                                                    \
void name##_DinsertNewNode(name##_DLL* DLL, type newData, int index)\
{                                                   \
    if(index < 0 || index >= DLL->length)           \
        return;                                     \
                                                    \
    name##_node* toBeConnected;                     \
    name##_node* newNode;                           \
    name##_node* current;                           \
    if(index == 0)/*New head*/                      \
    {                                               \
        name##_DAddNewNode(DLL, newData);           \
    }                                               \
    else if(index == DLL->length - 1)/*New tail*/   \
    {                                               \
        newNode = malloc(sizeof(name##_node));      \
        newNode->length = 2;                        \
        newNode->nodes = malloc(sizeof(name##_node *) * 2);\
        newNode->nodes[0] = DLL->tail;              \
        newNode->nodes[1] = NULL;                   \
        newNode->data = newData;                    \
        DLL->tail = newNode;                        \
    }                                               \
    else                                            \
    {                                               \
        current = DLL->head;                        \
        while(index > 1)                            \
        {                                           \
            if(current->nodes[1] == NULL)           \
            {                                       \
                return;                             \
            }                                       \
            else                                    \
            {                                       \
                current = current->nodes[1];        \
                index--;                            \
            }                                       \
        }                                           \
        toBeConnected = current->nodes[1];  	    \
        newNode = malloc(sizeof(name##_node));      \
        newNode->length = 2;                        \
        newNode->nodes = malloc(sizeof(name##_node *) * 2);\
        newNode->data = newData;                    \
        current->nodes[1] = newNode;                \
        newNode->nodes[0] = current;                \
        newNode->nodes[1] = toBeConnected;          \
        toBeConnected->nodes[0] = newNode;          \
    }                                               \
    DLL->length++;                                  \
    return;                                         \
}                                                   \
                                                    \
name##_GraphResult name##_DretrieveData(name##_DLL* DLL, int index)\
{                                                   \
    name##_GraphResult result = { 0 };              \
    if(index >= 0 && index < DLL->length)           \
    {                                               \
        name##_node* current = DLL->head;           \
        while(index > 0)                            \
        {                                           \
            if(current->nodes[1] == NULL)           \
            {                                       \
                return;                             \
            }                                       \
            else                                    \
            {                                       \
                current = current->nodes[1];        \
                index--;                            \
            }                                       \
        }                                           \
        result.success = 1;                         \
        result.value = current->data;               \
    }                                               \
    return result;                                  \
}                                                   \
                                                    \
int name##_DgetSize(name##_DLL* DLL)                \
{                                                   \
    if(DLL->head == NULL)                           \
    {                                               \
        DLL->length = 0;                            \
        return 0;                                   \
    }                                               \
                                                    \
    int length = 1;                                 \
    name##_node* current = DLL->head;               \
    while(current->nodes[1] != NULL)                \
    {                                               \
        current = current->nodes[1];                \
        length++;                                   \
    }                                               \
    DLL->length = length;                           \
    return length;                                  \
}                                                   \
                                                    \
void name##_DremoveItem(name##_DLL* DLL, int index) \
{                                                   \
    if(index < 0 || index >= DLL->length)           \
        return;                                     \
                                                    \
    name##_node* current;                           \
    name##_node* toBeRemoved;                       \
    name##_node* toBeConnected;                     \
                                                    \
    if(index == 0) /*the head*/                     \
    {                                               \
        toBeConnected = DLL->head->nodes[1];        \
        toBeRemoved = DLL->head;                    \
        DLL->head = toBeConnected;                  \
        free(toBeRemoved->nodes);                   \
        free(toBeRemoved);                          \
    }                                               \
    else if(index == DLL->length - 1)/*the tail*/   \
    {                                               \
        toBeConnected = DLL->tail->nodes[0];        \
        toBeRemoved = DLL->tail;                    \
        DLL->tail = toBeConnected;                  \
        free(toBeRemoved->nodes);                   \
        free(toBeRemoved);                          \
    }                                               \
    else                                            \
    {                                               \
        name##_node* current = DLL->head;           \
        while(index > 1)                            \
        {                                           \
            if(current->nodes[1] == NULL)           \
            {                                       \
                return;                             \
            }                                       \
            else                                    \
            {                                       \
                current = current->nodes[1];        \
                index--;                            \
            }                                       \
        }                                           \
        toBeRemoved = current->nodes[1];            \
        toBeConnected = toBeRemoved->nodes[1];      \
        current->nodes[1] = toBeConnected;          \
        toBeConnected->nodes[0] = current;          \
        free(toBeRemoved->nodes);                   \
        free(toBeRemoved);                          \
    }                                               \
    DLL->length--;                                  \
    return;                                         \
}                                                   \
                                                    \
void name##_DchangeValue(name##_DLL* DLL, int index, type newData)\
{                                                   \
    if(index < 0 || index >= DLL->length)           \
        return;                                     \
                                                    \
    name##_node* current = DLL->head;               \
    while(index > 0)                                \
    {                                               \
        if(current->nodes[1] == NULL)               \
        {                                           \
            return;                                 \
        }                                           \
        else                                        \
        {                                           \
            current = current->nodes[1];            \
            index--;                                \
        }                                           \
    }                                               \
    current->data = newData;                        \
}                                                   \
                                                    \
void name##_DdestroyLinkedList(name##_DLL* DLL)     \
{                                                   \
    name##_destroyGraph(DLL->head);                 \
    free(DLL);                                      \
}