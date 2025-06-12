#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define DEFINE_SET(type, name)              \
DEFINE_LIST(type, name);                    \
                                            \
typedef int (*name##_typecmp)(type input1, type input2);\
                                            \
typedef struct                              \
{                                           \
    name##_list* l;                         \
    name##_typecmp cmp;                     \
} name##_set;                               \
                                            \
                                            \
name##_set* name##_initializeSet(int newSize, name##_typecmp cmp);\
void name##_destroySet(name##_set* set);    \
int name##_addToSet(name##_set* set, type data);\
int name##_removeFromSet(name##_set* set, type data);\
int name##_setContains(name##_set* set, type data);\
void name##_setCombine(name##_set* origin, name##_set* setToBeConnected);