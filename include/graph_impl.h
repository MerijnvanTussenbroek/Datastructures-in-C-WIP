#pragma once

#define DEFINE_GRAPH(name, type)            \
                                            \
name##_node* name##_initializeGraph(char* name)\
{                                           \
    name##_node* node = malloc(sizeof(name##_node));\
    *node->name = *name;                    \
    node->nodes = malloc(sizeof(name##_node));\
    node->length = 1;                       \
    return node;                            \
}                                           \
                                            \
void name##_addNewNode(name##_node* node, char* name)\
{                                           \
    node->nodes = realloc(node->nodes, (node->length + 1) * sizeof(name##_node *));\
    name##_node* newNode = name##_initializeGraph(name);\
    newNode->length = 0;                    \
    newNode->nodes = NULL;                  \
    *node->nodes[node->length] = *newNode;  \
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
    free(nodeToBeRemoved);                  \
}                                           \
                                            \
void name##_addExistingNode(name##_node* origin, name##_node* nodeToBeAdded)\
{                                           \
    node->nodes = realloc(node->nodes, (node->length + 1) * sizeof(name##_node *));\
    *node->nodes[node->length] = *nodeToBeAdded;\
    node->length++;                         \
}                                           \
                                            \
void name##_destroyGraph(name##_node* node) \
{                                           \
    if(node->length > 0)                    \
    {                                       \
        for(int i = 0; i < node->length; i++)\
        {                                   \
            name##_destroyGraph(node->nodes[i]);\
        }                                   \
        free(node->nodes);                  \
    }                                       \
    free(node);                             \
}