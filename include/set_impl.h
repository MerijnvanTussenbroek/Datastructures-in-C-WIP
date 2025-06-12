#pragma once

#include "list_impl.h"

#define DEFINE_SET(type, name)  \
DEFINE_LIST(type, name);        \
                                \
name##_set* name##_initializeSet(int newSize, name##_typecmp cmp)\
{                               \
    name##_list* l = name##_listCreate(newSize);\
    name##_set* s = malloc(sizeof(name##_set));\
    s->l = l;                   \
    s->cmp = cmp;               \
    return s;                   \
}                               \
                                \
void name##_destroySet(name##_set* set)\
{                               \
    if(set == NULL)             \
        return;                 \
                                \
    if(set->l == NULL)          \
        return;                 \
                                \
    name##_deleteList(set->l);  \
    free(set);                  \
}                               \
                                \
int name##_addToSet(name##_set* set, type data)\
{                               \
    int isIn = 0;               \
    int size = set->l->size;    \
    for(int i = 0; i < size; i++)\
    {                           \
        if(set->cmp(data, set->l->data[i]) == 1)\
        {                       \
            isIn = 1;           \
            break;              \
        }                       \
    }                           \
    if(isIn == 0)               \
    {                           \
        name##_addToList(set->l, data);\
        return 1;               \
    }                           \
    return 0;                   \
}                               \
                                \
int name##_removeFromSet(name##_set* set, type data)\
{                               \
    int isIn = 0;               \
    int size = set->l->size;    \
    for(int i = 0; i < size; i++)\
    {                           \
        if(set->cmp(data, set->l->data[i]) == 1)\
        {                       \
            isIn = i;           \
            break;              \
        }                       \
    }                           \
                                \
    if(isIn == 0)               \
    {                           \
        return 0;               \
    }                           \
                                \
    name##_removeFromList(set->l, isIn);\
    return 1;                   \
}                               \
                                \
int name##_setContains(name##_set* set, type data)\
{                               \
    int size = set->l->size;    \
    for(int i = 0; i < size; i++)\
    {                           \
        if(set->cmp(data, set->l->data[i]) == 1)\
        {                       \
            return 1;           \
        }                       \
    }                           \
    return 0;                   \
}                               \
                                \
void name##_setCombine(name##_set* origin, name##_set* setToBeConnected)\
{                               \
    if(origin->cmp != setToBeConnected->cmp)\
        return;                 \
                                \
    int totalCapacity = origin->l->capacity + setToBeConnected->l->capacity;\
    name##_set* newSet = name##_initializeSet(totalCapacity, origin->cmp);\
    int size1 = origin->l->size;\
    int size2 = setToBeConnected->l->size;\
    for(int i = 0; i < size1; i++)\
    {                           \
        name##_addToSet(newSet, origin->l->data[i]);\
    }                           \
    for(int j = 0; j < size2; j++)\
    {                           \
        name##_addToSet(newSet, setToBeConnected->l->data[j]);\
    }                           \
    name##_deleteList(origin->l);\
    origin->l = newSet->l;      \
    free(newSet);               \
}                               