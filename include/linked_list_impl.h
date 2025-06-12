#pragma onced

#include "graph_impl.h"

#define DEFINE_LINKED_LIST(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
name##_LL* name##_initializeLinkedList(type newData)\
{                                       \
    name##_LL* LL = malloc(sizeof(name##_LL));\
    LL->list = name##_initializeNode(newData);\
    LL->totalLength = 1;                \
    return LL;                          \
}                                       \
                                        \
name##_node* name##_initializeNode(type newData)\
{                                       \
    name##_node* node = malloc(sizeof(name##_node));\
    node->nodes = malloc(sizeof(name##_node*));\
    node->nodes = NULL;                 \
    node->length = 1;                   \
    return node;                        \
}                                       \
                                        \
void name##_addNewNodeToLL(name##_LL* LL, type newData)\
{                                       \
    if(LL->list == NULL)                \
    {                                   \
        LL->list = name##_initializeNode(newData);\
    }                                   \
    else                                \
    {                                   \
        name##_node* current = LL->list;\
        while(current->nodes[0] != NULL)\
        {                               \
            current = current->nodes[0];\
        }                               \
        current->nodes[0] = name##_initializeNode(newData);\
    }                                   \
    LL->totalLength++;                  \
}                                       \
                                        \
void name##_insertNewNodeToLL(name##_LL* LL, type newData, int index)\
{                                       \
    if(LL->totalLength < index)         \
    {                                   \
        printf("Index too great");      \
        return;                         \
    }                                   \
    else                                \
    {                                   \
        LL->totalLength++;              \
        name##_node* newNode = name##_initializeNode(newData);\
        if(index == 0)                  \
        {                               \
            name##_node* nodeToConnect = LL->list;\
            newNode->nodes[0] = nodeToConnect;\
            LL->list = newNode;         \
        }                               \
        else                            \
        {                               \
            name##_node* current = LL->list;\
            while(index > 1)            \
            {                           \
                if(current->nodes[0] == NULL)\
                {                       \
                    printf("Trying to insert a node outside the lists bounds");\
                    return;             \
                }                       \
                else                    \
                {                       \
                    current = current->nodes[0];\
                    index--;            \
                }                       \
            }                           \
            name##_node* PreviousNode = current;\
            name##_node* NextNode = current->nodes[0];\
            PreviousNode->nodes[0] = newNode;\
            newNode->nodes[0] = NextNode;\
        }                               \
    }                                   \
}                                       \
                                        \
name##_GraphResult name##_retrieveDataFromLL(name##_LL* LL, int index)\
{                                       \
    name##_GraphResult result = { 0 };  \
    if(index > LL->totalLength)         \
        return result;                  \
                                        \
    name##_node* current = LL->list;    \
    while(index > 0)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
            return result;              \
                                        \
        current = current->nodes[0];    \
        index--;                        \
    }                                   \
    result.success = 1;                 \
    result.value = current->data;       \
    return result;                      \
}                                       \
                                        \
int name##_getSizeFromLL(name##_LL* LL) \
{                                       \
    int size = 0;                       \
    name##_node* current = LL->list;    \
    while(current != NULL)              \
    {                                   \
        current = current->nodes[0];    \
        size++;                         \
    }                                   \
    return size;                        \
}                                       \
                                        \
void name##_removeItemFromLL(name##_LL* LL, int index)\
{                                       \
    if(index > LL->totalLength)         \
    {                                   \
        printf("Can't remove a node outside the bounds of the LL");\
        return;                         \
    }                                   \
    else                                \
    {                                   \
        name##_node* nodeToBeRemoved;   \
        name##_node* nodeToBeConnected; \
        LL->totalLength--;              \
        if(index == 0)                  \
        {                               \
            nodeToBeRemoved = LL->list; \
            nodeToBeConnected = LL->list->nodes[0];\
            free(nodeToBeRemoved->nodes);\
            free(nodeToBeRemoved);      \
            LL->list = nodeToBeConnected;\
        }                               \
        else                            \
        {                               \
            name##_node* current = LL->list;\
            while(index > 1)            \
            {                           \
                if(current->nodes[0] == NULL)\
                {                       \
                    return;             \
                }                       \
                else                    \
                {                       \
                    current = current->nodes[0];\
                    index--;            \
                }                       \
            }                           \
            nodeToBeRemoved = current->nodes[0];\
            nodeToBeConnected = nodeToBeRemoved->nodes[0];\
            current->nodes[0] = nodeToBeConnected;\
            free(nodeToBeRemoved->nodes);\
            free(nodeTOBeRemoved);      \
        }                               \
    }                                   \
}                                       \
                                        \
void name##_changeValueInLL(name##_LL* LL, int index, type newData)\
{                                       \
    name##_node* current = LL->list;    \
    while(index > 0)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            return;                     \
        }                               \
        else                            \
        {                               \
            current = current->nodes[0];\
            index--;                    \
        }                               \
    }                                   \
    current->data = newData;            \
}                                       \
                                        \
void name##_destroyLinkedList(name##_LL* LL)\
{                                       \
    name##_destroyGraph(LL->list);    \
    free(LL);                         \
}                                       