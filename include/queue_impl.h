#pragma once

#include "double_linked_list_impl.h"

#define DEFINE_QUEUE(name, type)        \
DEFINE_DOUBLE_LINKED_LIST(name, type);  \
                                        \
name##_queue* name##_initializeQueue(type newData)\
{                                       \
    name##_queue* queue = malloc(sizeof(name##_queue));\
    queue->head = malloc(sizeof(name##_node *) * 1);\
    queue->tail = malloc(sizeof(name##_node *) * 1);\
    name##_node* firstNode = name##_initializeDLL(newData);\
    queue->head = firstNode;            \
    queue->tail = firstNode;            \
    queue->length = 1;                  \
    return queue;                       \
}                                       \
                                        \
void name##_enqueue(name##_queue* queue, type newData)\
{                                       \
    name##_DinsertNewNode(&(queue->head), newData, 0);\
    queue->length++;                    \
}                                       \
                                        \
name##_GraphResult name##_dequeue(name##_queue* queue)\
{                                       \
    name##_GraphResult result = { 0 };  \
    if(queue->length > 0)               \
    {                                   \
        name##_node* newTail = queue->tail->nodes[0];\
        result = name##_DretrieveData(queue->tail, 0);\
        name##_node* oldTail = queue->tail;\
        queue->tail = newTail;          \
        oldTail->nodes[0] = NULL;       \
        oldTail->nodes[1] = NULL;       \
        name##_DdestroyLinkedList(oldTail);\
        queue->length--;                       \
    }                                   \
    return result;                      \
}                                       \
                                        \
void name##_destroyQueue(name##_queue* queue)\
{                                       \
    name##_DdestroyLinkedList(queue->head);\
    free(queue->head);                  \
    free(queue->tail);                  \
    free(queue);                        \
}