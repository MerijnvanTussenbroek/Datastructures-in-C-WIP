#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashFunction(const void *data, size_t size);

#define DEFINE_HASHMAP(name, key, value)        \
                                                \
typedef struct name##_specialNode name##_specialNode;\
typedef struct name##_specialNode               \
{                                               \
    int isUsed;                                 \
    key theKey;                                 \
    value theValue;                             \
    name##_specialNode* next;                   \
};                                              \
                                                \
typedef struct name##_hashmap name##_hashmap;   \
typedef struct name##_hashmap                   \
{                                               \
    name##_specialNode** map;                   \
    size_t length;                              \
};                                              \
                                                \
                                                \
typedef void (*name##_callback)(key inputKey, const value inputValue);\
                                                \
name##_hashmap* name##_initializehashmap(int newSize);\
void name##_addToHashmap(name##_hashmap* map, key theKey, value newData, size_t dataSize);\
void name##_iterationFunc(name##_hashmap* map, name##_callback func);\
void name##_destroyHasmap(name##_hashmap* map);\
void name##_destroySpecialLL(name##_specialNode* next);\
name##_specialNode name##_searchBasedOnKey(name##_hashmap* map, key newKey, int (*cmp)(const key *, const key *));\
name##_specialNode name##_searchBasedOnValue(name##_hashmap* map, value newValue, int (*cmp)(const value *, const value *));