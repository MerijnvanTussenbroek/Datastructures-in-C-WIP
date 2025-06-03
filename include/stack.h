#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFINE_STACK(name, type)            \
DEFINE_LINKED_LIST(name,type);              \
                                            \
typedef name##_node name##_stack;           \
                                            \
void push(name##_stack* stack, type newData);\
name##_GraphResult pop(name##_stack* stack);\
