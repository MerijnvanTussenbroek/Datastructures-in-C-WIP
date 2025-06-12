#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t hashsetFunction(const void *data, size_t size);

#define DEFINE_HASHSET(name, key)               \
                                                \
typedef struct name##_specialNode name##_specialNode;\
typedef struct name##_specialNode               \
{                                               \
    int isUsed;                                 \
    key theKey;                                 \
    name##_specialNode* next;                   \
};                                              \
                                                \
typedef struct name##_hashset name##_hashset;   \
typedef struct name##_hashset                   \
{                                               \
    name##_specialNode** map;                   \
    size_t length;                              \
};                                              \
                                                \
typedef void (*name##_callback)(key inputKey);  \
typedef int (*name##_keycmp)(key input1, key input2);\
                                                \
name##_hashset* name##_initializehashset(int newSize);\
void name##_addToHashset(name##_hashset* set, key theKey, name##_keycmp cmp);\
void name##_iterationFunc(name##_hashset* set, name##_callback func);\
void name##_destroyHashset(name##_hashset* set);\
void name##_destroySpecialLL(name##_specialNode* next);\
int name##_contains(name##_hashset* set, key theKey, name##_keycmp cmp);