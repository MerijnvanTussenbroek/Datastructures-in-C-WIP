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
name##_BT* name##_initializeBT(type initialValue, name##_compFunc f)\
{                                       \
    name##_BT* bt = malloc(sizeof(name##_BT));\
    bt->root = malloc(sizeof(name##_node));\
    bt->f = f;                          \
    bt->root->length = 2;               \
    bt->root->nodes = malloc(sizeof(name##_node *) * 2);\
    bt->root->nodes[0] = NULL;          \
    bt->root->nodes[1] = NULL;          \
    bt->root->data = initialValue;      \
    return bt;                          \
}                                       \
                                        \
void name##_destroyBT(name##_BT* bt)    \
{                                       \
    \
}                                       \
                                        \
void name##_addToBT(name##_BT* bt, type value)\
{                                       \
    \
}                                       \
                                        \
void name##_BTRemoveByIndex(name##_BT* bt, int index)\
{                                       \
    \
}                                       \
                                        \
void name##_BTRemoveByValue(name##_BT* bt, type value)\
{                                       \
    \
}                                       \
                                        \
int name##_BTContains(name##_BT* bt, type value)\
{                                       \
    \
}                                       \
                                        \
name##_GraphResult name##_BTRetrieve(name##_BT* bt, int index)\
{                                       \
    \
}                                       \
                                        \
void name##_BTCombine(name##_BT* origin, name##_BT* BTToBeAdded)\
{                                       \
    \
}                                       \
                                        \
void name##_ReorganizeBT(name##_BT* bt) \
{                                       \
    \
}                                       \

