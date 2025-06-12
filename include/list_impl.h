#pragma once

#define DEFINE_LIST(type,name)\
/* datastructure initialization */      \
name##_list* name##_listCreate(int newSize)\
{                                       \
    name##_list* list = NULL;           \
    if(newSize > 0)                     \
    {                                   \
        list = malloc(sizeof(name##_list));\
        list->data = malloc(sizeof(type) * newSize);\
        list->size = 0;                 \
        list->capacity = newSize;       \
    }                                   \
    return list;                        \
}                                       \
                                        \
/* datastructure functions */           \
void name##_addToList(name##_list *l, type value)\
{                                       \
    if(l->size == l->capacity)          \
    {                                   \
        type* temp = realloc(l->data, sizeof(type) * (l->capacity + 4));\
        l->capacity += 4;               \
        if(!temp) exit(-1);             \
        l->data = temp;                 \
    }                                   \
    l->data[l->size++] = value;         \
}                                       \
                                        \
void name##_changeInList(name##_list *l, type value, int index)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried changeing an item that doesn't exist.");\
        return;                         \
    }                                   \
    l->data[index] = value;             \
}                                       \
                                        \
void name##_removeFromList(name##_list *l, int index)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried deleting an item that doesn't exist.");\
        return;                         \
    }                                   \
    for(int i = index; i < (l->size - 1); i++)\
    {                                   \
        l->data[i] = l->data[i+1];\
    }                                   \
    l->size--;                          \
}                                       \
                                        \
void name##_insertIntoListAt(name##_list *l, int index, type value)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried inserting an item at an index that deosn't exit.");\
        return;                         \
    }                                   \
                                        \
    if(l->size + 1 == l->capacity)      \
    {                                   \
        type* temp = realloc(l->data, sizeof(type) * (l->capacity + 4));\
        l->capacity += 4;               \
        if(!temp) exit(-1);             \
        l->data = temp;                 \
    }                                   \
                                        \
    for(int i = index; i < l->size; i++){\
        l->data[i+1] = l->data[i];      \
    }                                   \
    l->size++;                          \
    l->data[index] = value;             \
}                                       \
                                        \
void name##_deleteList(name##_list *l)  \
{                                       \
    if(!l) exit(-1);                    \
    if(!l->data) exit(-1);              \
    free(l->data);                      \
    free(l);                            \
}                                       \
                                        \
name##_result name##_retrieveFromList(name##_list *l, int index)\
{                                       \
    name##_result result =  { 0 };      \
    if(l->size < index || index < 0)    \
    {                                   \
        printf("Tried retrieving an item that doesn't exist. %d \n", index);\
        return result;                  \
    }                                   \
    result.success = 1;                 \
    result.value = l->data[index];      \
    return result;                      \
}                                       \
/* This only works if the type can be compared */\
/* To do this, youll have to define your own comparison function that must adhere to the following requirements */\
/* The output is an integer, if the first input is less than the second, return 1, otherwise return 0*/\
/*so for example, with 5 < 6 you return 1, but for 8 < 2 you return 0 or anything BUT 1*/\
void name##_sortList(name##_list *l, compare cmp)    \
{                                       \
    for(int i = 0; i < l->size; i++)    \
    {                                   \
        for(int j = i; j < l->size; j++)\
        {                               \
            if(cmp(l->data[i],l->data[j]) != 1)\
            {                           \
                type temp = l->data[i]; \
                l->data[i] = l->data[j];\
                l->data[j] = temp;      \
            }                           \
        }                               \
    }                                   \
}                                       \
/*The second list is freed and out into list 1*/\
void name##_combineLists(name##_list *l1, name##_list* l2)\
{                                       \
    int totalCapacity = l1->capacity + l2->capacity;\
    type* newList = malloc(sizeof(type) * totalCapacity);\
    int i = 0;                          \
    while(i < l1->size)                 \
    {                                   \
        newList[i] = l1->data[i];       \
        i++;                            \
    }                                   \
    int j = i;                          \
    while(i - j < l2->size)             \
    {                                   \
        newList[i] = l2->data[i-j];     \
        i++;                            \
    }                                   \
    free(l1->data);                     \
    l1->data = newList;                 \
    l1->capacity = totalCapacity;       \
    l1->size = i;                       \
    name##_deleteList(l2);              \
}