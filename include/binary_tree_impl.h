#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph_impl.h"

returnStruct turnIntoBinary(int num)
{
    int* result = (int *)calloc(16, sizeof(int) * 16);

    unsigned int input = (unsigned int)num;
    int loc = 0;

    returnStruct s = { 0 };

    while(input != 0)
    {
        result[loc] = input & 1;
        input = input >> 1;
        loc++;
    }

    s.list = result;
    s.length = loc;

    return s;
}

int determineNextPos(int* arr1, int* arr2)
{
    //array 1 is current location
    //array 2 is where to go
    int index1 = 15;

    while(arr1[index1] == 0)
    {
        index1--;
    }
    
    return arr2[index1];
}

int isItPossible(int* arr1, int* arr2)
{
    int index1 = 15;

    while(arr1[index1] == 0) //arr 1 is loc
    {
        index1--;
    }

    int index2 = 15;

    while(arr2[index2] == 0) //arr 2 is where to go
    {
        index2--;
    }

    int success = 1;

    while(index1 >= 0)
    {
        if(arr1[index1] != arr2[index2])
        {
            success = 0;
        }
        index1--;
        index2--;
    }

    return success;
}

//navigating using binary representations must be redone
//as the navigation does not currently work

#define DEFINE_BINARY_TREE(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
name##_BT* name##_initializeBT(type initialValue, name##_compFunc f)\
{                                       \
    name##_BT* bt = malloc(sizeof(name##_BT));\
    bt->f = f;                          \
    bt->root = malloc(sizeof(name##_node));\
    bt->root->data = initialValue;      \
    bt->length = 1;                     \
    bt->root->length = 2;               \
    bt->root->nodes = malloc(sizeof(name##_node *) * 2);\
    bt->root->nodes[0] = NULL;          \
    bt->root->nodes[1] = NULL;          \
    return bt;                          \
}                                       \
                                        \
static inline void name##_BTRemove1(name##_BT* bt, type value)\
{                                       \
    name##_BTRemoveByValue(bt->f, bt->root, value);\
}                                       \
                                        \
static inline void name##_BTRemove2(name##_BT* bt, int index)\
{                                       \
    returnStruct name##_s = turnIntoBinary(index);\
    name##_BTRemoveByIndex(bt->f, bt->root, 0, name##_s.list, name##_s.length);\
}                                       \
                                        \
static inline int name##_BTContains1(name##_BT* bt, type value)\
{                                       \
    return name##_BTContains(bt->f, bt->root, value);\
}                                       \
                                        \
static inline name##_GraphResult name##_BTRetrieve1(name##_BT* bt, int index)\
{                                       \
    returnStruct name##_s = turnIntoBinary(index);\
    return name##_BTRetrieve(bt->f, bt->root, 0, name##_s.list, name##_s.length);\
}                                       \
                                        \
static inline void name##_CombineBT1(name##_BT* bt1, name##_BT* bt2)\
{                                       \
    name##_BTCombine(bt1->f, bt1->root, bt2->root);\
    name##_ReorganizeBT(bt1);           \
    name##_destroyBT(bt2);              \
}                                       \
                                        \
void name##_destroyBT(name##_BT* bt)    \
{                                       \
    name##_destroyGraph(bt->root);      \
    free(bt);                           \
}                                       \
                                        \
void name##_addToBT(name##_compFunc f, name##_node* current, type value)\
{                                       \
    if(current->length != 2)            \
        return;                         \
                                        \
    name##_node* left = current->nodes[0];\
    name##_node* right = current->nodes[1];\
    int result = f(current->data, value);\
    if(result == 1)                     \
    {                                   \
        if(left == NULL)                \
        {                               \
            left = malloc(sizeof(name##_node));\
            left->length = 2;           \
            left->data = value;         \
            left->nodes = malloc(sizeof(name##_node *) * 2);\
            left->nodes[0] = NULL;      \
            left->nodes[1] = NULL;      \
            return;                     \
        }                               \
        else                            \
        {                               \
            name##_addToBT(f, left, value);\
        }                               \
    }                                   \
    else                                \
    {                                   \
        if(right == NULL)               \
        {                               \
            right = malloc(sizeof(name##_node));\
            right->length = 2;           \
            right->data = value;         \
            right->nodes = malloc(sizeof(name##_node *) * 2);\
            right->nodes[0] = NULL;      \
            right->nodes[1] = NULL;      \
            return;                     \
        }                               \
        else                            \
        {                               \
            name##_addToBT(f, right, value);\
        }                               \
    }                                   \
    return;                             \
}                                       \
                                        \
void name##_BTRemoveByIndex(name##_compFunc f, name##_node* current, int depth, int* moves, int length)\
{                                       \
    if(depth == length - 1)              \
    {                                   \
        name##_node* previous = current->nodes[moves[depth]];\
        name##_node* nodeToBeRemoved = current->nodes[moves[depth+1]];\
        name##_node* left = nodeToBeRemoved->nodes[0];\
        name##_node* right = nodeToBeRemoved->nodes[1];\
        previous->nodes[moves[depth]] = left;\
        name##_BTCombine(f, previous, right);\
        free(nodeToBeRemoved->nodes);   \
        free(nodeToBeRemoved);          \
        free(moves);                    \
    }                                   \
    else                                \
    {                                   \
        name##_BTRemoveByIndex(f, current->nodes[moves[depth]], depth+1, moves, length);\
    }                                   \
    return;                             \
}                                       \
                                        \
void name##_BTRemoveByValue(name##_compFunc f, name##_node* current, type value)\
{                                       \
    int result0 = f(current->data, value);\
    int result1 = f(current->nodes[0]->data, value);\
    int result2 = f(current->nodes[1]->data, value);\
                                        \
    name##_node* nodeToBeRemoved = NULL;\
                                        \
    if(result1 == 2)                    \
    {                                   \
        nodeToBeRemoved = current->nodes[0];\
    }                                   \
                                        \
    if(result2 == 2)                    \
    {                                   \
        nodeToBeRemoved = current->nodes[1];\
    }                                   \
                                        \
    if(nodeToBeRemoved != NULL)         \
    {                                   \
        name##_node* left = nodeToBeRemoved->nodes[0];\
        name##_node* right = nodeToBeRemoved->nodes[1];\
        if(result1 == 2)                \
        {                               \
            current->nodes[0] = left;   \
            name##_BTCombine(f, current, right);\
        }                               \
        else                            \
        {                               \
            current->nodes[1] = right;  \
            name##_BTCombine(f, current, left);\
        }                               \
        free(nodeToBeRemoved->nodes);   \
        free(nodeToBeRemoved);          \
    }                                   \
    else                                \
    {                                   \
        if(result0 == 1)                    \
        {                                   \
            name##_BTRemoveByValue(f, current->nodes[0], value);\
        }                                   \
        else                                \
        {                                   \
            name##_BTRemoveByValue(f, current->nodes[1], value);\
        }                                   \
    }                                   \
                                        \
    return;                             \
}                                       \
                                        \
int name##_BTContains(name##_compFunc f, name##_node* current, type value)\
{                                       \
    int result = f(current->data, value);\
    if(result == 2)                     \
    {                                   \
        return 1;                       \
    }                                   \
    if(current->nodes[0] == NULL && current->nodes[1] == NULL)\
    {                                   \
        return 0;                       \
    }                                   \
    if(current->nodes[0] == NULL)       \
    {                                   \
        return name##_BTContains(f, current->nodes[1], value);\
    }                                   \
    else if(current->nodes[1] == NULL)  \
    {                                   \
        return name##_BTContains(f, current->nodes[0], value);\
    }                                   \
    else                                \
    {                                   \
        if(result == 1)                 \
        {                               \
            return name##_BTContains(f, current->nodes[0], value);\
        }                               \
        else                            \
        {                               \
            return name##_BTContains(f, current->nodes[1], value);\
        }                               \
    }                                   \
}                                       \
                                        \
name##_GraphResult name##_BTRetrieve(name##_compFunc f, name##_node* current, int depth, int* moves, int length)\
{                                       \
                                        \
    if(depth == length)                 \
    {                                   \
        name##_GraphResult r = { 0 };   \
        r.success = 1;                  \
        r.value = current->data;        \
        return r;                       \
    }                                   \
    if(current->nodes[moves[depth]] == NULL)\
    {                                   \
        name##_GraphResult s = { 0 };   \
        s.success = 0;                  \
        return s;                       \
    }                                   \
    return name##_BTRetrieve(f, current->nodes[moves[depth]], depth+1, moves, length);\
}                                       \
                                        \
void name##_BTCombine(name##_compFunc f, name##_node* origin, name##_node* BTToBeAdded)\
{                                       \
    int result0 = f(origin->data, BTToBeAdded->data);\
    if(result0 == 1)                    \
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

