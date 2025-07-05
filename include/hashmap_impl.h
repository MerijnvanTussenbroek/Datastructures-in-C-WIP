#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashFunction(const void *data, size_t size)
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

#define DEFINE_HASHMAP(name, key, value)        \
                                                \
name##_hashmap* name##_initializehashmap(int newSize)\
{                                               \
    name##_hashmap* map = malloc(sizeof(name##_hashmap));\
    map->map = malloc(sizeof(name##_specialNode *) * newSize);\
    for(int i = 0; i < newSize; i++)            \
    {                                           \
        map->map[i] = NULL;                     \
    }                                           \
    map->length = newSize;                      \
    return map;                                 \
}                                               \
                                                \
void name##_addToHashmap(name##_hashmap* map, key* theKey, value* newData, size_t dataSize)\
{                                               \
    uint64_t hashValue = hashFunction((void *)theKey, dataSize);\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* newNode = malloc(sizeof(name##_specialNode));\
    newNode->isUsed = 1;                        \
    newNode->theKey = *theKey;                  \
    newNode->theValue = *newData;               \
    newNode->next = NULL;                       \
    if(map->map[index] != NULL)                 \
    {                                           \
        name##_specialNode* nextNode = map->map[index];\
        while(nextNode->next != NULL)           \
        {                                       \
            if(nextNode->isUsed == 0)           \
            {                                   \
                nextNode->isUsed = 1;           \
                nextNode->theKey = *theKey;     \
                nextNode->theValue = *newData;  \
                free(newNode);                  \
                return;                         \
            }                                   \
            else                                \
            {                                   \
                nextNode = nextNode->next;      \
            }                                   \
        }                                       \
        nextNode->next = newNode;               \
    }                                           \
    else                                        \
    {                                           \
            map->map[index] = newNode;          \
    }                                           \
}                                               \
                                                \
void name##_iterationFunc(name##_hashmap* map, name##_callback func)\
{                                               \
    if(map == NULL)                             \
        return;                                 \
                                                \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        if(map->map[i] != NULL)                 \
        {                                       \
            name##_specialNode* next = map->map[i];\
            while(next != NULL)                 \
            {                                   \
                if(next->isUsed == 1)           \
                {                               \
                    func(next->theKey, next->theValue);\
                }                               \
                next = next->next;              \
            }                                   \
        }                                       \
    }                                           \
}                                               \
                                                \
void name##_destroyHashmap(name##_hashmap* map)  \
{                                               \
    if(map == NULL)                             \
        return;                                 \
                                                \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        if(map->map[i] != NULL)                 \
        {                                       \
            name##_destroySpecialLL(map->map[i]);\
        }                                       \
    }                                           \
    free(map->map);                             \
    free(map);                                  \
}                                               \
                                                \
void name##_destroySpecialLL(name##_specialNode* next)\
{                                               \
    name##_specialNode* current = next;         \
    if(current != NULL)                         \
    {                                           \
        if(current->next != NULL)               \
        {                                       \
            name##_destroySpecialLL(current->next);\
        }                                       \
        free(current);                          \
    }                                           \
}                                               \
                                                \
int name##_containsHashmap1(name##_hashmap* map, key* theKey, int (*cmp)(key *, key *))\
{                                               \
    uint64_t hashValue = hashFunction((void *)theKey, sizeof(key));\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* n = map->map[index];    \
    while(n != NULL)                            \
    {                                           \
        if(cmp(theKey, &n->theKey) == 1)        \
            return 1;                           \
        n = n->next;                            \
    }                                           \
    return 0;                                   \
}                                               \
                                                \
int name##_containsHashmap2(name##_hashmap* map, value* theValue, int (*cmp)(value *, value *))\
{                                               \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        name##_specialNode* n = map->map[i];    \
        while(n != NULL)                        \
        {                                       \
            if(cmp(theValue, &n->theValue) == 1)\
                return 1;                       \
            n = n->next;                        \
        }                                       \
    }                                           \
    return 0;                                   \
}                                               \
                                                \
int name##_removeFromHashmap1(name##_hashmap* map, key* theKey, int (*cmp)(key *, key *))\
{                                               \
    uint64_t hashValue = hashFunction((void *)theKey, sizeof(key));\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* n = map->map[index];    \
    while(n != NULL)                            \
    {                                           \
        if(cmp(theKey, &n->theKey) == 1)        \
        {                                       \
            n->isUsed = 0;                      \
            return 1;                           \
        }                                       \
        n = n->next;                            \
    }                                           \
    return 0;                                   \
}                                               \
                                                \
int name##_removeFromHashmap2(name##_hashmap* map, value* theValue, int (*cmp)(value *, value *))\
{                                               \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        name##_specialNode* n = map->map[i];    \
        while(n != NULL)                        \
        {                                       \
            if(cmp(theValue, &n->theValue) == 1)\
            {                                   \
                n->isUsed = 0;                  \
                return 1;                       \
            }                                   \
            n = n->next;                        \
        }                                       \
    }                                           \
    return 0;                                   \
}                                               \
                                                \
name##_specialNode name##_searchBasedOnKey(name##_hashmap* map, key* newKey, int (*cmp)(key *, key *))  \
{                                               \
    name##_specialNode result = { 0 };          \
    result.next = NULL;                         \
    result.isUsed = 0;                          \
    if(map == NULL)                             \
        return result;                          \
                                                \
    uint64_t hashValue = hashFunction((void *)newKey, sizeof(key));\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* nodes = map->map[index];\
    while(cmp(&nodes->theKey, newKey) != 1 && nodes->next != NULL)\
    {                                           \
        nodes = nodes->next;                    \
    }                                           \
    if(cmp(&nodes->theKey, newKey) == 1)        \
    {                                           \
        result = *nodes;                        \
    }                                           \
    return result;                              \
}                                               \
                                                \
name##_specialNode name##_searchBasedOnValue(name##_hashmap* map, value* newValue, int (*cmp)(value *, value *))  \
{                                               \
    name##_specialNode result = { 0 };          \
    result.isUsed = 0;                          \
    result.next = NULL;                         \
    if(map == NULL)                             \
        return result;                          \
                                                \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        if(map->map[i] != NULL)                 \
        {                                       \
            name##_specialNode* next = map->map[i];\
            while(next != NULL)                 \
            {                                   \
                if(cmp(newValue, &next->theKey) == 1)\
                {                               \
                    return *next;               \
                }                               \
                next = next->next;              \
            }                                   \
        }                                       \
    }                                           \
    return result;                              \
}
