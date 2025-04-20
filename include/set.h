#include <stdlib.h>
#include <stdio.h>

#define DEFINE_SET(type, name)              \
typedef struct                              \
{                                           \
    type *data;                             \
    int size;                               \
    int capacity;                           \
} name##_set;                               \
                                            \
name##_set* name##_setCreate(int newSize)   \
{                                           \
    name##_set* set;                        \
    set = malloc(sizeof(name##_set));       \
    set->data = malloc(sizeof(type) * (newSize + 4));\
    set->size = 0;                   \
    set->capacity = newSize + 4;           \
    return set;                             \
}                                           \
                                            \
void name##_addToSet(name##_set *s, type value, int (*cmp)(const type *, const type *))\
{                                           \
    if(s->size == s->capacity)              \
    {                                       \
        type* temp = realloc(s->data, sizeof(type) * (s->capacity + 2));\
        s->capacity += 2;                   \
        s->size += 2;                       \
        if(!temp) exit(-1);                 \
        s->data = temp;                     \
    }                                       \
    for(int i = 0; i < s->size; i++)        \
    {                                       \
        if(cmp(&s->data[i], &value) == 2)   \
        {                                   \
            return;                         \
        }                                   \
    }                                       \
    s->data[s->size++] = value;             \
}                                           \
                                            \
/* The cmp function must return 2 if they're equal*/\
void name##_removeFromSet(name##_set *s, type value, int (*cmp)(const type *, const type *))\
{                                           \
    for(int i = 0; i < s->size; i++)        \
    {                                       \
        if(cmp(&s->data[i], &value) == 2)   \
        {                                   \
            for(int j = i; j < s->size-1; j++)\
            {                               \
                s->data[j] = s->data[j+1];  \
            }                               \
            break;                          \
        }                                   \
                                            \
    }                                       \
}                                           \
                                            \
int name##_isInSet(name##_set *s, type value, int (*cmp)(const type *, const type *))\
{                                           \
    for(int i = 0; i < s->size; i++)        \
    {                                       \
        if(cmp(&s->data[i], &value) == 2)   \
            return 1;                       \
    }                                       \
    return 0;                               \
}                                           \
                                            \
void name##_deleteSet(name##_set *s)        \
{                                           \
    if(!s) return;                          \
    if(!s->data) return;                    \
    free(s->data);                          \
    free(s);                                \
}