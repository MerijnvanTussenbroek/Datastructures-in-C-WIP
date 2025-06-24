#pragma once
#include <stdlib.h>
#include <stdio.h>


#define DEFINE_LIST(type, name)         \
typedef struct name##_list name##_list; \
typedef struct name##_list              \
{                                       \
    type *data;                         \
    int size;                           \
    int capacity;                       \
};                                      \
                                        \
typedef struct name##_result name##_result;\
typedef struct name##_result            \
{                                       \
    int success;                        \
    type value;                         \
};                                      \
                                        \
typedef int (*name##_compare)(type input1, type input2);\
                                        \
name##_list* name##_listCreate(int newSize);\
void name##_addToList(name##_list *l, type value);\
void name##_changeInList(name##_list *l, type value, int index);\
void name##_removeFromList(name##_list *l, int index);\
void name##_insertIntoListAt(name##_list *l, int index, type value);\
void name##_deleteList(name##_list *l);\
name##_result name##_retrieveFromList(name##_list *l, int index);\
void name##_sortList(name##_list *l, name##_compare cmp);\
void name##_combineLists(name##_list *l1, name##_list* l2);

