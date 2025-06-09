#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashFunction(const void *data, size_t size)
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

#define DEFINE_HASHMAP(name, key, value)        \
                                                \
name##_hashmap* name##_initializehashmap(int newSize)     \
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
void name##_addToHashmap(name##_hashmap* map, key theKey, value newData, size_t dataSize)\
{                                               \
    uint64_t hashValue = hashFunction((void *)theKey, dataSize);\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* newNode = malloc(sizeof(name##_specialNode));\
    newNode->isUsed = 1;                        \
    newNode->theKey = theKey;                   \
    newNode->theValue = newData;                \
    newNode->next = NULL;                       \
    if(map->map[index] != NULL)                 \
    {                                           \
        name##_specialNode* nextNode = map->map[index];\
        while(nextNode->next != NULL)           \
        {                                       \
            nextNode = nextNode->next;          \
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
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        if(map->map[i] != NULL)                 \
        {                                       \
            name##_specialNode* next = map->map[i];\
            while(next->next != NULL)           \
            {                                   \
                func(next->theKey, next->theValue);\
                next = next->next;              \
            }                                   \
        }                                       \
    }                                           \
}                                               \
                                                \
void name##_destroyHasmap(name##_hashmap* map)  \
{                                               \
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
name##_specialNode name##_searchBasedOnKey(name##_hashmap* map, key newKey, int (*cmp)(const key *, const key *))  \
{                                               \
    name##_specialNode result;                  \
    uint64_t hashValue = hashFunction((void *)newKey, sizeof(newKey));\
    int index = (int)(hashValue % map->length); \
    name##_specialNode* nodes = map->map[index];\
    int i = 0;                                  \
    result = nodes[i];                          \
    while(cmp(&result.theKey, &newKey) != 1 && result.next != NULL)\
    {                                           \
        result = *result.next;                  \
    }                                           \
    return result;                              \
}                                               \
                                                \
name##_specialNode name##_searchBasedOnValue(name##_hashmap* map, value newValue, int (*cmp)(const value *, const value *))  \
{                                               \
    name##_specialNode result = { 0 };          \
    result.isUsed = 0;                          \
    result.next = NULL;                         \
    for(int i = 0; i < map->length; i++)        \
    {                                           \
        if(map->map[i] != NULL)                 \
        {                                       \
            name##_specialNode* next = map->map[i];\
            while(next->next != NULL)           \
            {                                   \
                if(cmp(&newValue, &next->theKey) == 1)\
                {                               \
                    return *next;               \
                }                               \
                next = next->next;              \
            }                                   \
        }                                       \
    }                                           \
    return result;                              \
}
