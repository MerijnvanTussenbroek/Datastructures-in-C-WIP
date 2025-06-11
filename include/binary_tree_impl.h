#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph_impl.h"

int* turnIntoBinary(int num)
{
    int* result = (int *)calloc(16, sizeof(int) * 16); // 2 bytes

    unsigned int input = (unsigned int)num;
    int loc = 0;

    while(input != 0)
    {
        result[loc] = input & 1;
        input = input >> 1;
        loc++;
    }

    return result;
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

#define DEFINE_BINARY_TREE(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
static inline void name##_removeFromBinTree(name##_node* node, int index, name##_compFunc cmp)\
{                                       \
    int* loc2 = turnIntoBinary(index);  \
    int* loc1 = turnIntoBinary(1);      \
    if(isItPossible(loc1, loc2) == 1)   \
    {                                   \
        name##_removeFromBT(node, index, 1, cmp);\
        name##_reorganiseBT(node, cmp); \
    }                                   \
    else                                \
    {                                   \
        printf("Trying to remove a node from an impossible locations\n");\
    }                                   \
    free(loc1);                         \
    free(loc2);                         \
    return;                             \
}                                       \
                                        \
static inline name##_GraphResult name##_retrieveFromBinTree(name##_node* node, int index, name##_compFunc cmp)\
{                                       \
    int* loc2 = turnIntoBinary(index);  \
    int* loc1 = turnIntoBinary(1);      \
    if(isItPossible(loc1, loc2) == 1)   \
    {                                   \
        free(loc1);                     \
        free(loc2);                     \
        return name##_retrieveFromBT(node, index, 1, cmp);\
    }                                   \
    else                                \
    {                                   \
        free(loc1);                     \
        free(loc2);                     \
        printf("Trying to remove a node from an impossible locations\n");\
        name##_GraphResult result = { 0 };\
        return result;                  \
    }                                   \
}                                       \
                                        \
name##_node* name##_initializeBinaryTree(type newData)\
{                                       \
    name##_node* BT = malloc(sizeof(name##_node));\
    BT->data = newData;                 \
    BT->nodes = malloc(sizeof(name##_node *) * 2);\
    BT->nodes[0] = NULL;                \
    BT->nodes[1] = NULL;                \
    BT->length = 2;                     \
    return BT;                          \
}                                       \
                                        \
void name##_addToBT(name##_node* node, type newData, name##_compFunc cmp)\
{                                       \
    int result = cmp(newData, node->data);\
    if(result == 1) /* newData < node->data*/\
    {                                   \
        if(node->nodes[0] == NULL)      \
        {                               \
            name##_node* newRightNode;  \
            newRightNode = name##_initializeBinaryTree(newData);\
            node->nodes[0] = newRightNode;\
        }                               \
        else                            \
        {                               \
            name##_addToBT(node->nodes[0], newData, cmp);\
        }                               \
    }                                   \
    else  /* newData >= node->data*/    \
    {                                   \
        if(node->nodes[1] == NULL)      \
        {                               \
            name##_node* newLeftNode;   \
            newLeftNode = name##_initializeBinaryTree(newData);\
            node->nodes[1] = newLeftNode;\
        }                               \
        else                            \
        {                               \
            name##_addToBT(node->nodes[1], newData, cmp);\
        }                               \
    }                                   \
}                                       \
                                        \
void name##_addNodeToBT(name##_node* origin, name##_node* toBeAdded, name##_compFunc cmp)\
{                                       \
int result = cmp(toBeAdded->data, origin->data);\
    if(result == 1) /* toBeAdded->data < origin->data*/\
    {                                   \
        if(origin->nodes[0] == NULL)    \
        {                               \
            origin->nodes[0] = toBeAdded;\
        }                               \
        else                            \
        {                               \
            name##_addNodeToBT(origin->nodes[0], toBeAdded, cmp);\
        }                               \
    }                                   \
    else  /* toBeAdded->data >= node->data*/    \
    {                                   \
        if(origin->nodes[1] == NULL)      \
        {                               \
            origin->nodes[1] = toBeAdded;\
        }                               \
        else                            \
        {                               \
            name##_addNodeToBT(origin->nodes[1], toBeAdded, cmp);\
        }                               \
    }                                   \
}                                       \
                                        \
void name##_removeFromBT(name##_node* node, int index, int location, name##_compFunc cmp)\
{                                       \
    name##_node* nodeToBeRemoved;       \
    name##_node* child1;                \
    name##_node* child2;                \
    int result;                         \
    if(location * 2 == index)           \
    {                                   \
        nodeToBeRemoved = node->nodes[0];\
    }                                   \
    else if(location * 2 + 1 == index)  \
    {                                   \
        nodeToBeRemoved = node->nodes[1];\
    }                                   \
    else                                \
    {                                   \
        int* loc1 = turnIntoBinary(location);\
        int* loc2 = turnIntoBinary(index);\
        int nextPost = determineNextPos(loc1, loc2);\
        if(nextPost == 1)               \
        {                               \
            name##_removeFromBT(node->nodes[1], index, location * 2 + 1, cmp);\
        }                               \
        else                            \
        {                               \
            name##_removeFromBT(node->nodes[0], index, location * 2, cmp);\
        }                               \
        free(loc1);                     \
        free(loc2);                     \
    }                                   \
    child1 = nodeToBeRemoved->nodes[0]; \
    child2 = nodeToBeRemoved->nodes[1]; \
    name##_addNodeToBT(child1, child2, cmp);\
                                        \
    if(location * 2 == index)           \
    {                                   \
        node->nodes[0] = child1;        \
    }                                   \
    else if(location * 2 + 1 == index)  \
    {                                   \
        node->nodes[0] = child2;        \
    }                                   \
    return;                             \
}                                       \
                                        \
void name##_reorganiseBT(name##_node* node, name##_compFunc cmp)\
{                                       \
    /*yet to be implemented*/\
}                                       \
                                        \
void name##_deleteBT(name##_node* node) \
{                                       \
    if(node->nodes[0] != NULL)          \
    {                                   \
        name##_deleteBT(node->nodes[0]);\
    }                                   \
    if(node->nodes[1] != NULL)          \
    {                                   \
        name##_deleteBT(node->nodes[1]);\
    }                                   \
    free(node->nodes);                  \
    free(node);                         \
}                                       \
                                        \
name##_GraphResult name##_retrieveFromBT(name##_node* node, int index, int location, name##_compFunc cmp)\
{                                       \
    if(location == index)               \
    {                                   \
        name##_GraphResult result = { 0 };\
        result.success = 1;             \
        result.value = node->data;       \
        return result;                  \
    }                                   \
    else                                \
    {                                   \
        int* loc1 = turnIntoBinary(location);\
        int* loc2 = turnIntoBinary(index);\
        int nextPost = determineNextPos(loc1, loc2);\
        free(loc1);                     \
        free(loc2);                     \
        if(nextPost == 1)               \
        {                               \
            return name##_retrieveFromBT(node->nodes[1], index, location * 2 + 1, cmp);\
        }                               \
        else                            \
        {                               \
            return name##_retrieveFromBT(node->nodes[0], index, location * 2, cmp);\
        }                               \
    }                                   \
}                                       
