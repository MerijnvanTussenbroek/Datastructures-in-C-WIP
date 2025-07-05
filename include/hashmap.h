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
typedef void (*name##_callback)(key inputKey, value inputValue);\
                                                \
name##_hashmap* name##_initializehashmap(int newSize);\
void name##_addToHashmap(name##_hashmap* map, key* theKey, value* newData, size_t dataSize);\
void name##_iterationFunc(name##_hashmap* map, name##_callback func);\
void name##_destroyHashmap(name##_hashmap* map);\
void name##_destroySpecialLL(name##_specialNode* next);\
int name##_containsHashmap1(name##_hashmap* map, key* theKey, int (*cmp)(key *, key *));\
int name##_containsHashmap2(name##_hashmap* map, value* theValue, int (*cmp)(value *, value *));\
int name##_removeFromHashmap1(name##_hashmap* map, key* theKey, int (*cmp)(key *, key *));\
int name##_removeFromHashmap2(name##_hashmap* map, value* theValue, int (*cmp)(value *, value *));\
name##_specialNode name##_searchBasedOnKey(name##_hashmap* map, key* newKey, int (*cmp)(key *, key *));\
name##_specialNode name##_searchBasedOnValue(name##_hashmap* map, value* newValue, int (*cmp)(value *, value *));