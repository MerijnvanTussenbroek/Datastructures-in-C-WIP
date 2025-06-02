#include "double_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/*
if we have a queue: a <-> b <-> c <-> d
we assume a is the head, and d is the tail
so if we say dequeue, we return d
if we say enqueue, it goes before a
*/

#define DEFINE_QUEUE(name, type)    \
DEFINE_DOUBLE_LINKED_LIST(name, type); \
typedef struct name##_queue name##_queue; \
typedef struct name##_queue \
{ \
    name##_node* head; \
    name##_node* tail; \
}; \
 \
typedef struct \
{ \
    int success; \
    type value; \
} name##_queueResult; \
 \
name##_queue* name##_initializeQueue(type* newData); \
void name##_enqueue(name##_queue* queue, type* newData); \
name##_queueResult name##_dequeue(name##_queue* queue); \
void name##_destroyQueue(name##_queue* queue); \