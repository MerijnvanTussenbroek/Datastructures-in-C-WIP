#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "list_impl.h"

#define DEFINE_DICTIONAIRY(key, value, name)                \
DEFINE_LIST(key, name##_keyList);                           \
DEFINE_LIST(value, name##_valueList);                       \
                                                            \
name##_dictionary* name##_initializeDictionary(int newSize) \
{                                                           \
    name##_dictionary* dict = malloc(sizeof(name##_dictionary));\
    dict->keys = name##_keyList_listCreate(newSize);        \
    dict->values = name##_valueList_listCreate(newSize);    \
    return dict;                                            \
}                                                           \
                                                            \
void name##_addToDictionary(name##_dictionary* dict, key newKey, value newValue)\
{                                                           \
    name##_keyList_addToList(dict->keys, newKey);           \
    name##_valueList_addToList(dict->values, newValue);     \
}                                                           \
                                                            \
name##_dictResult name##_searchBasedOnKey(name##_dictionary* dict, key newKey, int (*cmp)(const key *, const key *))\
{                                                           \
    int index = -1;                                       \
    for(int i = 0; i < dict->keys->size; i++)               \
    {                                                       \
        if(cmp(&newKey, &dict->keys->data[i]) == 1)         \
        {                                                   \
            index = i;                                      \
        }                                                   \
    }                                                       \
                                                            \
    name##_dictResult result = { 0 };                       \
                                                            \
    if(index == -1)                                       \
    {                                                       \
        result.success = 0;                                 \
    }                                                       \
    else                                                    \
    {                                                       \
        result.success = 1;                                 \
        result.theKey = dict->keys->data[index];            \
        result.theValue = dict->values->data[index];        \
    }                                                       \
    return result;                                          \
}                                                           \
                                                            \
name##_dictResult name##_searchBasedOnValue(name##_dictionary* dict, value newValue, int (*cmp)(const value *, const value *))\
{                                                           \
    int index = -1;                                       \
    for(int i = 0; i < dict->values->size; i++)             \
    {                                                       \
        if(cmp(&newValue, &dict->values->data[i]) == 1)     \
        {                                                   \
            index = i;                                      \
        }                                                   \
    }                                                       \
                                                            \
    name##_dictResult result = { 0 };                       \
                                                            \
    if(index == -1)                                       \
    {                                                       \
        result.success = 0;                                 \
    }                                                       \
    else                                                    \
    {                                                       \
        result.success = 1;                                 \
        result.theKey = dict->keys->data[index];            \
        result.theValue = dict->values->data[index];        \
    }                                                       \
    return result;                                          \
}                                                           \
                                                            \
void name##_destroyDictionary(name##_dictionary* dict)      \
{                                                           \
    name##_keyList_deleteList(dict->keys);                  \
    name##_valueList_deleteList(dict->values);              \
    free(dict);                                             \
}