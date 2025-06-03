#pragma once

#include "linked_list_impl.h"

#define DEFINE_STACK(name, type)            \
DEFINE_LINKED_LIST(name,type);              \
                                            \
void push(name##_stack* stack, type newData)\
{                                           \
    name##_insertNewNodeToLL((name##_node **)&stack, newData, 0);\
}                                           \
                                            \
name##_GraphResult pop(name##_stack* stack) \
{                                           \
    name##_GraphResult result = name##_retrieveDataFromLL((name##_node *)stack, 0);\
    name##_removeItemFromLL((name##_node **)&stack, 0);\
    return result;                          \
}