#include <stdlib.h>
#include <stdio.h>

#define DEFINE_DOUBLE_LINKED_LIST(name, type)       \
typedef struct name##_Dnode name##_Dnode;           \
typedef struct name##_Dnode                         \
{                                                   \
    type data;                                      \
    name##_Dnode* next;                             \
    name##_Dnode* previous;                         \
    int size;                                       \
};                                                  \
                                                    \
typedef struct                                      \
{                                                   \
    int success;                                    \
    type* value;                                    \
} name##_DLLresult;                                 \
                                                    \
name##_Dnode* name##_DinitializeDLL(type* data);      \
void name##_DaddNewNode(name##_Dnode* list, type* newData);\
void name##_DinsertNewNode(name##_Dnode* list, type* newData, int index);\
name##_DLLresult name##_DretrieveData(name##_Dnode * list, int index);\
int name##_DgetSize(name##_Dnode * list);\
void name##_DremoveItem(name##_Dnode* list, int index);\
void name##_DchangeValue(name##_Dnode* list, int index, type* newData);\
void name##_DdestroyLinkedList(name##_Dnode* list);\

