#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashsetFunction(const void *data, size_t size)
{
    const unsigned char* bytes = (const unsigned char *)data;

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
name##_hashset* name##_initializehashset(int newSize, name##_keycmp cmp)\
{                                   \
    name##_hashset* set = malloc(sizeof(name##_hashset));\
    set->map = malloc(sizeof(name##_specialNode *) * newSize);\
    for(int i = 0; i < newSize; i++)\
    {                               \
        set->map[i] = NULL;         \
    }                               \
    set->length = newSize;          \
    set->cmp = cmp;                 \
    return set;                     \
}                                   \
                                    \
void name##_addToHashset(name##_hashset* set, key theKey)\
{                                   \
    int index = (int)(hashsetFunction((void *)&theKey, sizeof(theKey)) % set->length);\
    name##_specialNode* node = malloc(sizeof(name##_specialNode));\
    node->isUsed = 1;               \
    node->theKey = theKey;          \
    node->next = NULL;              \
    if(set->map[index] == NULL)     \
    {                               \
        set->map[index] = node;     \
    }                               \
    else                            \
    {                               \
        name##_specialNode* current = set->map[index];\
        while(current->next != NULL)\
        {                           \
            if(current->isUsed == 0)\
            {                       \
                current->isUsed = 1;\
                current->theKey = theKey;\
                free(node);         \
                return;             \
            }                       \
            else                    \
            {                       \
                current = current->next;\
            }                       \
        }                           \
        current->next = node;       \
    }                               \
}                                   \
                                    \
void name##_iterationFunc(name##_hashset* set, name##_callback func)\
{                                   \
    for(int i = 0; i < set->length; i++)\
    {                               \
        name##_specialNode* current = set->map[i];\
        while(current != NULL)      \
        {                           \
            if(current->isUsed == 1)\
                func(current->theKey);\
            current = current->next;\
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
int name##_containsHashset(name##_hashset* set, key theKey)\
{                                   \
    int index = (int)(hashsetFunction((void *)&theKey, sizeof(theKey)) % set->length);\
    name##_specialNode* current = set->map[index];\
    while(current != NULL)          \
    {                               \
        if(set->cmp(current->theKey, theKey) == 1)\
            return 1;               \
                                    \
        current = current->next;    \
    }                               \
                                    \
    return 0;                       \
}                                   \
                                    \
int name##_removeFromHashset(name##_hashset* set, key theKey)\
{                                   \
    int index = (int)(hashsetFunction((void *)&theKey, sizeof(theKey)) % set->length);\
    name##_specialNode* current = set->map[index];\
    while(current != NULL)          \
    {                               \
        if(set->cmp(theKey, current->theKey) == 1)\
        {                           \
            current->isUsed = 0;    \
            return 1;               \
        }                           \
        else                        \
        {                           \
            current = current->next;\
        }                           \
    }                               \
    return 0;                       \
}                                   