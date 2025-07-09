#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#define DEFINE_DICTIONAIRY(key, value, name)                \
DEFINE_LIST(key, name##_keyList);                           \
DEFINE_LIST(value, name##_valueList);                       \
                                                            \
typedef struct name##_dictionary name##_dictionary;         \
typedef struct name##_dictionary                            \
{                                                           \
    name##_keyList_list* keys;                              \
    name##_valueList_list* values;                          \
};                                                          \
                                                            \
typedef struct name##_dictResult name##_dictResult;         \
typedef struct name##_dictResult                            \
{                                                           \
    int success;                                            \
    key theKey;                                             \
    value theValue;                                         \
};                                                          \
                                                            \
name##_dictionary* name##_initializeDictionary(int newSize);                   \
void name##_addToDictionary(name##_dictionary* dict, key newKey, value newValue);\
name##_dictResult name##_searchBasedOnKey(name##_dictionary* dict, key newKey, int (*cmp)(const key *, const key *));\
name##_dictResult name##_searchBasedOnValue(name##_dictionary* dict, value newValue, int (*cmp)(const value *, const value *));\
void name##_iterateOverDict(name##_dictionary* dic, void (*callback)(key *, value *));\
void name##_destroyDictionary(name##_dictionary* dict);