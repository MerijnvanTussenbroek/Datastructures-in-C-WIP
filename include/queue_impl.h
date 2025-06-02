#pragma once

#include "double_linked_list_impl.h"

#define DEFINE_QUEUE(name, type) \
DEFINE_DOUBLE_LINKED_LIST(name, type); \
 \
name##_queue* name##_initializeQueue(type* newData) \
{ \
    name##_queue* queue = (name##_queue *)malloc(sizeof(name##_queue)); \
    queue->head = name##_DinitializeDLL(newData); \
    queue->tail = queue->head; \
} \
 \
void name##_enqueue(name##_queue* queue, type* newData) \
{ \
    name##_Dnode* head = queue->head; \
}