#pragma once

#include "set_impl.h"

#define DEFINE_GRAPH(name, type)            \
DEFINE_SET(name##_node* , name);            \
                                            \
name##_node* name##_initializeGraph(type newData)\
{                                           \
    name##_node* node = malloc(sizeof(name##_node));\
    node->length = 0;                       \
    node->nodes = NULL;                     \
    node->data = newData;                   \
    return node;                            \
}                                           \
                                            \
void name##_addNewNode(name##_node* node, type newData)\
{                                           \
    node->nodes = realloc(node->nodes, (node->length + 1) * sizeof(name##_node *));\
    name##_node* newNode = name##_initializeGraph(newData);\
    node->nodes[node->length] = newNode;    \
    node->length++;                         \
}                                           \
                                            \
void name##_removeNode(name##_node* node, int index)\
{                                           \
    if(index < 0 || index > node->length-1) \
        return;                             \
                                            \
    name##_node* nodeToBeRemoved = node->nodes[index];\
    for(int i = index; i < (node->length)-1; i++)   \
    {                                       \
        node->nodes[i] = node->nodes[i+1];  \
    }                                       \
    free(nodeToBeRemoved->nodes);           \
    free(nodeToBeRemoved);                  \
}                                           \
                                            \
void name##_addExistingNode(name##_node* origin, name##_node* nodeToBeAdded)\
{                                           \
    origin->nodes = realloc(origin->nodes, (origin->length + 1) * sizeof(name##_node *));\
    *origin->nodes[origin->length] = *nodeToBeAdded;\
    origin->length++;                         \
}                                           \
                                            \
void name##_destroyGraph(name##_node* node) \
{                                           \
    name##_set* s = name##_initializeSet(10, name##_cmpFunc);\
    name##_CollectAllNodes(node, s);        \
    int size = s->l->size;                  \
    for(int i = 0; i < size; i++)           \
    {                                       \
        free(s->l->data[i]->nodes);         \
        free(s->l->data[i]);                \
    }                                       \
}                                           \
                                            \
int name##_cmpFunc(name##_node* node1, name##_node* node2)\
{                                           \
    if(node1->nodes == node2->nodes)        \
    {                                       \
        return 1;                           \
    }                                       \
    return 0;                               \
}                                           \
                                            \
void name##_CollectAllNodes(name##_node* node, name##_set* s)\
{                                           \
    if(node == NULL)                        \
        return;                             \
                                            \
    if(s == NULL)                           \
        return;                             \
                                            \
    if(s->l == NULL)                        \
        return;                             \
                                            \
    if(name##_addToSet(s, node) == 0)       \
    {                                       \
        return;                             \
    }                                       \
    else                                    \
    {                                       \
        for(int i = 0; i < node->length; i++)\
        {                                   \
            if(node->nodes[i] != NULL)      \
                name##_CollectAllNodes(node->nodes[i], s);\
        }                                   \
    }                                       \
}