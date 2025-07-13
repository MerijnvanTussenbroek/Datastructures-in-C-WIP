#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph_impl.h"

//navigating using binary representations must be redone
//as the navigation does not currently work

#define DEFINE_BINARY_TREE(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
name##_BT* name##_initializeBT(type initialValue, name##_compFunc f)\
{/*When you have input a and b into f, that is f(a,b), if a < b then f returns 1*/\
    name##_BT* bt = malloc(sizeof(name##_BT));\
    bt->f = f;                          \
    bt->root = malloc(sizeof(name##_node));\
    bt->root->data = initialValue;      \
    bt->length = 1;                     \
    bt->root->length = 2;               \
    bt->root->nodes = malloc(sizeof(name##_node *) * 2);\
    bt->root->nodes[0] = NULL;          \
    bt->root->nodes[1] = NULL;          \
    bt->count = 0;                      \
    return bt;                          \
}                                       \
                                        \
static inline void name##_BTAdd(name##_BT* bt, type value)\
{                                       \
    name##_addToBT(bt->f, bt->root, value);\
    bt->count++;                        \
    if(bt->count > 9)                   \
        name##_ReorganizeBT(bt);        \
}                                       \
                                        \
static inline void name##_BTRemove(name##_BT* bt, type value)\
{                                       \
    name##_BTRemoveByValue(bt->f, bt->root, value);\
    bt->count++;                        \
    if(bt->count > 9)                   \
        name##_ReorganizeBT(bt);        \
}                                       \
                                        \
static inline int name##_BTContains(name##_BT* bt, type value)\
{                                       \
    bt->count++;                        \
    if(bt->count > 9)                   \
        name##_ReorganizeBT(bt);        \
    return name##_BTContainsfunc(bt->f, bt->root, value);\
}                                       \
                                        \
static inline void name##_CombineBT(name##_BT* bt1, name##_BT* bt2)\
{                                       \
    name##_BTCombine(bt1->f, bt1->root, bt2->root);\
    name##_ReorganizeBT(bt1);           \
    free(bt2);                          \
}                                       \
                                        \
void name##_destroyBT(name##_BT* bt)    \
{                                       \
    name##_destroyGraph(bt->root);      \
    free(bt);                           \
}                                       \
                                        \
name##_node* name##_createNewNode(type value)\
{                                       \
    name##_node* node = malloc(sizeof(name##_node));\
    node->data = value;                 \
    node->length = 2;                   \
    node->nodes = malloc(sizeof(name##_node *) * 2);\
    node->nodes[0] = NULL;              \
    node->nodes[1] = NULL;              \
    return node;                        \
}                                       \
                                        \
void name##_addToBT(name##_compFunc f, name##_node* current, type value)\
{                                       \
    int result = f(value, current->data);\
    if(result == 1)                     \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            current->nodes[0] = name##_createNewNode(value);\
        }                               \
        else                            \
        {                               \
            name##_addToBT(f, current->nodes[0], value);\
        }                               \
    }                                   \
    else                                \
    {                                   \
        if(current->nodes[1] == NULL)   \
        {                               \
            current->nodes[1] = name##_createNewNode(value);\
        }                               \
        else                            \
        {                               \
            name##_addToBT(f, current->nodes[1], value);\
        }                               \
    }                                   \
}                                       \
                                        \
                                        \
void name##_BTRemoveByValue(name##_compFunc f, name##_node* current, type value)\
{                                       \
    int result = f(value, current->data);\
    if(result == 2)                     \
    {                                   \
        name##_node* leftNode = current->nodes[0];\
        name##_node* rightNode = current->nodes[1];\
                                        \
        if(rightNode == NULL)           \
        {                               \
            current->data = leftNode->data;\
            current->nodes[0] = leftNode->nodes[0];\
            current->nodes[1] = leftNode->nodes[1];\
            free(leftNode->nodes);      \
            free(leftNode);             \
            return;                     \
        }                               \
        else                            \
        {                               \
            name##_node* rightleftNode = rightNode->nodes[0];\
            name##_node* rightrightNode = rightNode->nodes[1];\
                                        \
            current->data = rightNode->data;\
            current->nodes[0] = rightleftNode;\
            current->nodes[1] = rightrightNode;\
                                        \
            free(rightNode->nodes);     \
            free(rightNode);            \
            return;                     \
        }                               \
    }                                   \
    else if(result == 1)                \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            return;                     \
        }                               \
        else                            \
        {                               \
            name##_BTRemoveByValue(f, current->nodes[0], value);\
        }                               \
    }                                   \
    else                                \
    {                                   \
        if(current->nodes[1] == NULL)   \
        {                               \
            return;                     \
        }                               \
        else                            \
        {                               \
            name##_BTRemoveByValue(f, current->nodes[1], value);\
        }                               \
    }                                   \
}                                       \
                                        \
int name##_BTContainsfunc(name##_compFunc f, name##_node* current, type value)\
{/*if current->data == value, the f(value, current->data) returns 2*/\
    int result = f(value, current->data);\
    if(result == 2)                     \
    {                                   \
        return 1;                       \
    }                                   \
    else if(result == 1)                \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            return 0;                   \
        }                               \
        else                            \
        {                               \
            return name##_BTContainsfunc(f, current->nodes[0], value);\
        }                               \
    }                                   \
    else                                \
    {                                   \
        if(current->nodes[1] == NULL)   \
        {                               \
            return 0;                   \
        }                               \
        else                            \
        {                               \
            return name##_BTContainsfunc(f, current->nodes[1], value);\
        }                               \
    }                                   \
    return 0;                           \
}                                       \
                                        \
void name##_BTCombine(name##_compFunc f, name##_node* origin, name##_node* BTToBeAdded)\
{                                       \
    int result = f(BTToBeAdded->data, origin->data);\
    if(result == 1)                     \
    {                                   \
        if(origin->nodes[0] == NULL)    \
        {                               \
            origin->nodes[0] = BTToBeAdded;\
        }                               \
        else                            \
        {                               \
            name##_BTCombine(f, origin->nodes[0], BTToBeAdded);\
        }                               \
    }                                   \
    else                                \
    {                                   \
        if(origin->nodes[1] == NULL)    \
        {                               \
            origin->nodes[1] = BTToBeAdded;\
        }                               \
        else                            \
        {                               \
            name##_BTCombine(f, origin->nodes[1], BTToBeAdded);\
        }                               \
    }                                   \
}                                       \
                                        \
void name##_ReorganizeBT(name##_BT* bt) \
{                                       \
    name##_set* s = name##_initializeSet(bt->length, name##_cmpFunc);\
    name##_CollectAllNodes(bt->root, s);\
    name##_node** list = s->l->data;    \
    int length = s->l->size;            \
    name##_node* newRoot = bt->root;    \
                                        \
    int amountOfNodesLess = 0;          \
    int middle = length / 2;            \
    int deviation = length / 10;        \
                                        \
    int previousInspection = 0;         \
    for(int i = 0; i < length; i++)     \
    {                                   \
        name##_node* nodeToBeInspected = list[i];\
        name##_node* toBeCompared;      \
        for(int j = 0 ; j < length; j++)\
        {                               \
            toBeCompared = list[j];     \
            if(bt->f(nodeToBeInspected->data, toBeCompared->data) > 0)\
                amountOfNodesLess += 1; \
        }                               \
        if(amountOfNodesLess >= middle - deviation && amountOfNodesLess <= middle + deviation)\
        {                               \
            int diff = length - previousInspection;\
            int diff2 = length - amountOfNodesLess;\
            if(diff2 < diff)            \
            {                           \
                newRoot = toBeCompared; \
                previousInspection = amountOfNodesLess;\
            }                           \
        }                               \
                                        \
        amountOfNodesLess = 0;          \
    }                                   \
                                        \
    name##_removeFromSet(s, newRoot);   \
    length = s->l->size;                \
    for(int i = 0; i < length; i++)     \
    {                                   \
        name##_BTCombine(bt->f, newRoot, s->l->data[i]);\
    }                                   \
    bt->root = newRoot;                 \
}                                       \

