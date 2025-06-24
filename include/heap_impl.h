#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree_impl.h"

/*This is a max-heap or min-heap depending on the comparison function you give*/
//nodes[0] is left, nodes[1] is right, nodes[2] is the previous node
#define DEFINE_HEAP(name, type)     \
DEFINE_BINARY_TREE(name, type);     \
                                    \
name##_heap* name##_initializeHeap(type data, name##_HeapCompFunc f)\
{                                   \
    name##_heap* heap = malloc(sizeof(name##_heap));\
    heap->length = 1;               \
    heap->f = f;                    \
    heap->root = malloc(sizeof(name##_node));\
    heap->root->data = data;        \
    heap->root->length = 3;         \
    heap->root->nodes = malloc(sizeof(name##_node *) * 3);\
    heap->root->nodes[0] = NULL;    \
    heap->root->nodes[1] = NULL;    \
    heap->root->nodes[2] = NULL;    \
    heap->indexOfNextEmptySlot = 2; \
    return heap;                    \
}                                   \
                                    \
void name##_destroyHeap(name##_heap* heap)\
{                                   \
    name##_destroyGraph(heap->root);\
    free(heap);                     \
}                                   \
                                    \
int name##_addToHeap(name##_HeapCompFunc f, name##_node* current, type value, int* moves, int depth)\
{                                   \
    if(depth < 0 || current == NULL)\
    {                               \
        return 0;                   \
    }                               \
    if(depth == 0)                  \
    {                               \
        name##_node* newNode = malloc(sizeof(name##_node));\
        newNode->nodes = malloc(sizeof(name##_node*) * 3);\
        newNode->nodes[0] = NULL;   \
        newNode->nodes[1] = NULL;   \
        newNode->nodes[2] = current;   \
        newNode->data = value;      \
        current->nodes[moves[0]] = newNode;\
        return 1;                   \
    }                               \
    else if(depth == 1)             \
    {                               \
        name##_node* nodeBefore = current->nodes[moves[1]];\
        name##_node* newNode = malloc(sizeof(name##_node));\
        newNode->nodes = malloc(sizeof(name##_node*) * 3);\
        newNode->nodes[0] = NULL;   \
        newNode->nodes[1] = NULL;   \
        newNode->nodes[2] = NULL;   \
        newNode->data = value;      \
        nodeBefore->nodes[moves[0]] = newNode;\
        name##_RestoreHeapBalance(f, newNode);\
        return 1;                   \
    }                               \
    else                            \
    {                               \
        return name##_addToHeap(f, current->nodes[moves[depth]], value, moves, depth-1);\
    }                               \
}                                   \
                                    \
int name##_removeFromHeapIndex(name##_HeapCompFunc f, name##_node* current, int* moves, int depth)\
{                                   \
    if(depth < 0 || current == NULL)\
    {                               \
        return 0;                   \
    }                               \
    if(depth == 0)/*We're removing the root*/\
    {                               \
        \
    }                               \
    else if(depth == 1)/*We're removing a non-root node*/\
    {                               \
        \
    }                               \
    else                            \
    {                               \
        name##_removeFromHeapIndex(f, current->nodes[moves[depth]], moves, depth-1);\
    }                               \
}                                   \
                                    \
int name##_removeFromHeapValue(name##_HeapCompFunc f, name##_node* current, type value)\
{                                   \
    /*We assume there is only 1 of this value in the tree*/\
    /*and otherwise we remove both*/\
    int result = f(value, current->data);\
    if(result == 1) /*current->data > value*/\
    {                               \
        return 0;                   \
    }                               \
    if(result == 2) /*current->data == value*/\
    {                               \
        int x = f(current->nodes[0]->data, current->nodes[1]->data);\
        name##_node* left = current->nodes[0];\
        name##_node* right = current->nodes[1];\
        name##_node* upperNode = current->nodes[2];\
        int isItLeft = f(current->data, upperNode->nodes[0]->data);\
        if(x == 1)/*current->nodes[0]->data < current->nodes[1]->data*/\
        {                           \
            if(isItLeft == 2)       \
            {                       \
                upperNode->nodes[0] = right;\
                name##_HeapAddNode(f, right, left);\
            }                       \
            else                    \
            {                       \
                upperNode->nodes[1] = right;\
                name##_HeapAddNode(f, right, left);\
            }                       \
        }                           \
        else                        \
        {                           \
            if(isItLeft == 2)       \
            {                       \
                upperNode->nodes[0] = left;\
                name##_HeapAddNode(f, left, right);\
            }                       \
            else                    \
            {                       \
                upperNode->nodes[1] = left;\
                name##_HeapAddNode(f, left, right);\
            }                       \
        }                           \
        free(current->nodes);       \
        free(current);              \
        return 1;                   \
    }                               \
    else                            \
    {                               \
        int a = name##_removeFromHeapValue(f, current->nodes[0], value);\
        int b = name##_removeFromHeapValue(f, current->nodes[1], value);\
        if(a == 1)                  \
            return 1;               \
                                    \
        if(b == 1)                  \
            return 1;               \
                                    \
        return 0;                   \
    }                               \
}                                   \
                                    \
int name##_ContainsHeap(name##_HeapCompFunc f, name##_node* current, type value)\
{                                   \
    if(current == NULL)             \
        return 0;                   \
                                    \
    int result = f(value, current->data);\
    if(result == 2)                 \
    {                               \
        return 1;                   \
    }                               \
    else                            \
    {                               \
        int a = 0;                  \
        int b = 0;                  \
        if(current->nodes[0] == NULL || current->nodes[1] == NULL)\
        {                           \
            return 0;               \
        }                           \
        a = name##_ContainsHeap(f, current->nodes[0], value);\
        b = name##_ContainsHeap(f, current->nodes[1], value);\
                                    \
        if(a == 1)                  \
            return 1;               \
                                    \
        if(b == 1)                  \
            return 1;               \
                                    \
        return 0;                   \
    }                               \
}                                   \
                                    \
name##_GraphResult name##_HeapRetrieve(name##_HeapCompFunc f, name##_node* current, int* moves, int depth)\
{                                   \
    if(depth == 0)                  \
    {                               \
        name##_GraphResult r = { 0 };\
        r.success = 1;              \
        r.value = current->data;    \
        return r;                   \
    }                               \
    else                            \
    {                               \
        return name##_HeapRetrieve(f, current->nodes[moves[depth]], moves, depth-1);\
    }                               \
}                                   \
                                    \
void name##_HeapAddNode(name##_HeapCompFunc f, name##_node* origin, name##_node* nodeToBeAdded)\
{                                   \
    int result = f(origin->data, nodeToBeAdded->data);\
    if(result != 1)/*origin->data > nodeToBeAdded->data*/\
    {                               \
        name##_node* left = origin->nodes[0];\
        name##_node* right = origin->nodes[1];\
        if(left == NULL)            \
        {                           \
            left = nodeToBeAdded;   \
            return;                 \
        }                           \
        if(right == NULL)           \
        {                           \
            right = nodeToBeAdded;  \
            return;                 \
        }                           \
        int a = f(left->data, nodeToBeAdded->data);\
        if(a == 1)/*left->data < nodeToBeAdded->data*/\
        {                           \
            origin->nodes[0] = nodeToBeAdded;\
            name##_HeapAddNode(f, nodeToBeAdded, left);\
            return;                 \
        }                           \
        int b = f(right->data, nodeToBeAdded->data);\
        if(b == 1)/*left->data < nodeToBeAdded->data*/\
        {                           \
            origin->nodes[1] = nodeToBeAdded;\
            name##_HeapAddNode(f, nodeToBeAdded, right);\
            return;                 \
        }                           \
        name##_HeapAddNode(f, origin->nodes[1], nodeToBeAdded);\
    }                               \
    else                            \
    {                               \
        name##_HeapAddNode(f, origin->nodes[2], nodeToBeAdded);\
    }                               \
}                                   \
                                    \
void name##_RestoreHeapBalance(name##_HeapCompFunc f, name##_node* current)\
{                                   \
    name##_node* upperNode = current->nodes[2];\
    if(upperNode == NULL)           \
        return;                     \
                                    \
    int result = f(current->data, upperNode->data);\
    if(result == 1) /*current->data < upperNode->data*/\
    {                               \
        return;                     \
    }                               \
    else                            \
    {                               \
        type temp = current->data;  \
        current->data = upperNode->data;\
        upperNode->data = temp;     \
        name##_RestoreHeapBalance(f, upperNode);\
    }                               \
}                               