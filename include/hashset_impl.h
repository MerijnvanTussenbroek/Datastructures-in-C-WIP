#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashsetFunction(const void *data, size_t size)
{
    const uint64_t* bytes = (const uint64_t *)data;

    uint64_t hash = 12327598275924385904ULL;

    for(size_t i = 0; i < size; i++)
    {
        hash ^= bytes[i];
        hash *= 37852938529846ULL;
    }

    return hash;
}

#define DEFINE_HASHSET(name, key)   \
                                    \
name##_hashset* name##_initializehashset(int newSize)\
{                                   \
    name##_hashset* set = malloc(sizeof(name##_hashset));\
    set->map = malloc(sizeof(name##_specialNode *) * newSize);\
    for(int i = 0; i < newSize; i++)\
    {                               \
        set->map[i] = malloc(sizeof(name##_specialNode));\
        set->map[i]->next = NULL;   \
        set->map[i]->isUsed = 0;    \
    }                               \
    set->length = newSize;          \
    return set;                     \
}                                   \
                                    \
void name##_addToHashset(name##_hashset* set, key theKey)\
{                                   \
    int index = (int)(hashsetFunction((void *)theKey, sizeof(theKey)) % set->length);\
    name##_specialNode* node = malloc(sizeof(name##_specialNode));\
    node->isUsed = 1;               \
    node->theKey = theKey;          \
    node->next = NULL;              \
    if(set->map[index]->isUsed == 0)\
    {                               \
        free(set->map[index]);      \
        set->map[index] = node;     \
    }                               \
    else                            \
    {                               \
        name##_specialNode* current = set->map[index];\
        while(current->next != NULL)\
            current = current->next;\
                                    \
        current->next = node;       \
    }                               \
}                                   \
                                    \
void name##_iterationFunc(name##_hashset* set, name##_callback func)\
{                                   \
    for(int i = 0; i < set->length; i++)\
    {                               \
        if(set->map[i]->isUsed == 1)\
        {                           \
            name##_specialNode* current = set->map[i];\
            while(current != NULL)  \
            {                       \
                func(current->theKey);\
                current = current->next;\
            }                       \
        }                           \
    }                               \
}                                   \
                                    \
void name##_destroyHashset(name##_hashset* set)\
{                                   \
    for(int i = 0; i < set->length; i++)\
    {                               \
        if(set->map[i] != NULL)     \
        {                           \
            name##_destroySpecialLL(set->map[i]);\
        }                           \
    }                               \
    free(set->map);                 \
    free(set);                      \
}                                   \
                                    \
void name##_destroySpecialLL(name##_specialNode* next)\
{                                   \
    if(next->next != NULL)          \
    {                               \
        name##_destroySpecialLL(next->next);\
    }                               \
    free(next);                     \
}                                   \
                                    \
int name##_contains(name##_hashset* set, key theKey, name##_keycmp cmp)\
{                                   \
    int index = (int)(hashsetFunction((void *)theKey, sizeof(theKey)) % set->length);\
    name##_specialNode* current = set->map[index];\
    while(current != NULL)          \
    {                               \
        if(cmp(current->theKey, theKey) == 1)\
            return 1;               \
                                    \
        current = current->next;    \
    }                       \
                            \
    return 0;               \
}                                   