#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "graph_impl.h"

#define DEFINE_TREE(name, type)     \
DEFINE_GRAPH(name, type);           \
                                    \
name##_tree* name##_initializeTree(type newData)\
{                                   \
    name##_tree* t = malloc(sizeof(name##_tree));\
    t->root = malloc(sizeof(name##_node));\
    t->root->nodes = NULL;          \
    t->root->data = newData;        \
    t->amount = 1;                  \
    t->root->length = 0;            \
    return t;                       \
}                                   \
                                    \
void name##_destroyTree(name##_tree* t)\
{                                   \
    name##_destroyGraph(t->root);   \
    free(t);                        \
}                                   \
                                    \
void name##_addToTree(name##_node* n, int* setOfMoves, int length, int depth, type newData)\
{                                   \
    if(depth == length - 1)         \
    {                               \
        /*We are at the right node*/\
        name##_node** nodes = n->nodes;\
        nodes = realloc(nodes, sizeof(name##_node *) * (n->length + 1));\
        n->length++;                \
        n->nodes[n->length-1] = malloc(sizeof(name##_node));\
        name##_node* newNode = n->nodes[n->length-1];\
        newNode->data = newData;    \
        newNode->nodes = NULL;      \
        newNode->length = 0;        \
    }                               \
    else                            \
    {                               \
        int nextMove = setOfMoves[depth];\
        if(nextMove >= n->length)   \
        {                           \
            return;                 \
        }                           \
        name##_addToTree(n->nodes[nextMove], setOfMoves, length, depth+1, newData);\
    }                               \
}                                   \
                                    \
void name##_changeValueInTree(name##_node* n, int* setOfMoves, int length, int depth, type newData)\
{                                   \
    if(depth == length - 1)         \
    {                               \
        /*We are at the right node*/\
        name##_node** nodes = n->nodes;\
        name##_node* current = nodes[length - 1];\
        current->data = newData;    \
    }                               \
    else                            \
    {                               \
        int nextMove = setOfMoves[depth];\
        if(nextMove >= n->length)   \
        {                           \
            return;                 \
        }                           \
        name##_changeValueInTree(n->nodes[nextMove], setOfMoves, length, depth+1, newData);\
    }                               \
}                                   \
                                    \
void name##_removeFromTree(name##_node* n, int* setOfMoves, int length, int depth, type newData)\
{                                   \
    if(depth == length - 1)         \
    {                               \
        /*We are at the right node*/\
        name##_node** nodes = n->nodes;\
        n->length--;                \
        name##_node* toBeRemoved = nodes[length-1];\
        for(int i = length-1; i < n->length - 1; i++)\
        {                           \
            nodes[i] = nodes[i+1];  \
        }                           \
        name##_destroyGraph(toBeRemoved);\
    }                               \
    else                            \
    {                               \
        int nextMove = setOfMoves[depth];\
        if(nextMove >= n->length)   \
        {                           \
            return;                 \
        }                           \
        name##_removeFromTree(n->nodes[nextMove], setOfMoves, length, depth+1, newData);\
    }                               \
}