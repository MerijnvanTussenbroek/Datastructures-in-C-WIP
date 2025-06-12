#pragma once

#include "double_linked_list_impl.h"

#define DEFINE_QUEUE(name, type)        \
DEFINE_DOUBLE_LINKED_LIST(name, type);  \
                                        \
name##_queue* name##_initializeQueue(type newData)\
{                                       \
    name##_queue* queue = malloc(sizeof(name##_queue));\
    queue->DLL = name##_initializeDLL(newData);\
    return queue;                       \
}                                       \
                                        \
void name##_enqueue(name##_queue* queue, type newData)\
{                                       \
    name##_DaddNewNode(queue->DLL, newData);\
}                                       \
                                        \
name##_GraphResult name##_dequeue(name##_queue* queue)\
{                                       \
    int index = queue->DLL->length - 1; \
    name##_GraphResult result = name##_DretrieveData(queue->DLL, index);\
    name##_DremoveItem(queue->DLL, index);\
    return result;                      \
}                                       \
                                        \
void name##_destroyQueue(name##_queue* queue)\
{                                       \
    name##_DdestroyLinkedList(queue->DLL);\
    free(queue);                        \
}