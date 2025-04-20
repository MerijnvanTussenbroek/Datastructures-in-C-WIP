#include <stdlib.h>
#include <stdio.h>


#define DEFINE_LIST(type, name)         \
typedef struct                          \
{                                       \
    type *data;                         \
    int size;                           \
    int capacity;                       \
} name##_list;                          \
                                        \
/* datastructure initialization */      \
name##_list* name##_listCreate(int newSize)                                         \
{                                                                                   \
    name##_list* list;                                                              \
    list = malloc(sizeof(name##_list));                                             \
    list->data = malloc((sizeof(type) * newSize) + (4 * sizeof(type)));             \
    list->size = newSize;                                                           \
    list->capacity = (4 * sizeof(type)) + (sizeof(type) * newSize);                 \
    return list;                        \
}                                       \
                                        \
/* datastructure functions */           \
void name##_addToList(name##_list *l, type value)\
{                                       \
    if(l->size == l->capacity)          \
    {                                   \
        type* temp = realloc(l->data, l->capacity * 2);\
        l->capacity *= 2;               \
        if(!temp) exit(1);              \
        l->data = temp;                 \
    }                                   \
    l->data[l->size++] = value;         \
}                                       \
                                        \
void name##_changeInList(name##_list *l, type value, int index)\
{                                       \
    if(l->size < index){                \
        printf("Tried changeing an item that doesn't exist.");\
        return;                         \
    }                                   \
    l->data[index] = value;             \
}                                       \
                                        \
void name##_removeFromList(name##_list *l, int index)\
{                                       \
    if(l->size < index){                \
        printf("Tried deleting an item that doesn't exist.");\
        return;                         \
    }                                   \
    for(int i = index; i < (l->size - 1); i++)\
    {                                   \
        l->data[index] = l->data[index+1];\
    }                                   \
    l->size--;                          \
}                                       \
                                        \
void name##_deleteList(name##_list *l)  \
{                                       \
    printf("Begin deleting list\n");      \
    if(!l) return;                      \
    printf("Pointer is valid, begin deleting\n");    \
    if(!l->data) {printf("l->data is corrupt or null"); return;} \
    free(l->data);                      \
    printf("Deleted data, deleting list itself\n"); \
    free(l);                            \
}                                       \
                                        \
type name##_retrieveFromList(name##_list *l, int index)\
{                                       \
    if(l->size < index)                 \
    {                                   \
        printf("Tried retrieving an itme that doesn't exist.");\
    }                                   \
    return l->data[index];              \
}