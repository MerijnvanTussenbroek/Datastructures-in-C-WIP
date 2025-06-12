#include "double_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/*
if we have a queue: a <-> b <-> c <-> d
we assume a is the head, and d is the tail
so if we say dequeue, we return d and delete it from the list
if we say enqueue, it goes before a
*/

#define DEFINE_QUEUE(name, type)                            \
DEFINE_DOUBLE_LINKED_LIST(name, type);                      \
typedef struct name##_queue name##_queue;                   \
typedef struct name##_queue                                 \
{                                                           \
    name##_DLL* DLL;                                        \
};                                                          \
                                                            \
name##_queue* name##_initializeQueue(type newData);         \
void name##_enqueue(name##_queue* queue, type newData);     \
name##_GraphResult name##_dequeue(name##_queue* queue);     \
void name##_destroyQueue(name##_queue* queue);              