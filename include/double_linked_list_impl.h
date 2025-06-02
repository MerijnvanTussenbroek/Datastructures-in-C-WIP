#pragma once

#define DEFINE_DOUBLE_LINKED_LIST(name, type)       \
name##_Dnode* name##_DinitializeDLL(type* data)     \
{                                                   \
    name##_Dnode* list = malloc(sizeof(name##_Dnode));\
    list->data = *data;                             \
    list->next = NULL;                              \
    list->previous = NULL;                          \
    list->size = 1;                                 \
    return list;                                    \
}                                                   \
                                                    \
void name##_DaddNewNode(name##_Dnode* list, type* newData)\
{                                                   \
    if(list->next == NULL)                          \
    {                                               \
        name##_Dnode* newNode = name##_DinitializeDLL(newData);\
        list->next = newNode;                       \
        newNode->previous = list;                   \
    }                                               \
    else                                            \
    {                                               \
        name##_DaddNewNode(list->next, newData);      \
    }                                               \
}                                                   \
                                                    \
void name##_DinsertNewNode(name##_Dnode* list, type* newData, int index)\
{                                                   \
    if(index > 0 && list->next == NULL)             \
        return;                                     \
                                                    \
    if(index == 0)                                  \
    {                                               \
        name##_Dnode* specialCase = name##_DinitializeDLL(newData);\
        name##_Dnode* newNextNode = list;           \
        specialCase->next = list;                   \
        list->previous = specialCase;               \
        *list = *specialCase;                       \
        return;                                     \
    }                                               \
                                                    \
    if(index > 1)                                   \
    {                                               \
        name##_DinsertNewNode(list->next, newData, index-1);\
    }                                               \
    else                                            \
    {                                               \
        name##_Dnode* current = list;               \
        name##_Dnode* next = list->next;            \
        name##_Dnode* newNode = name##_DinitializeDLL(newData);\
        list->next = newNode;                       \
        newNode->previous = list;                   \
        next->previous = newNode;                   \
        newNode->next = next;                       \
    }                                               \
}                                                   \
                                                    \
name##_DLLresult name##_DretrieveData(name##_Dnode* list, int index)\
{                                                   \
    name##_DLLresult result = { 0 };                \
    if(list->next == NULL && index > 0)             \
    {                                               \
        return result;                              \
    }                                               \
                                                    \
    if(index > 0)                                   \
    {                                               \
        result = name##_DretrieveData(list->next, index-1);\
    }                                               \
    else                                            \
    {                                               \
        result.success = 1;                         \
        result.value = &list->data;                 \
    }                                               \
    return result;                                  \
}                                                   \
                                                    \
int name##_DgetSize(name##_Dnode* list)             \
{                                                   \
    if(list->next == NULL)                          \
    {                                               \
        return 1;                                   \
    }                                               \
    else                                            \
    {                                               \
        return 1 + name##_DgetSize(list->next);     \
    }                                               \
}                                                   \
                                                    \
void name##_DremoveItem(name##_Dnode* list, int index)\
{                                                   \
    if(index > 0 && list->next == NULL)             \
        return;                                     \
                                                    \
    if(index > 1)                                   \
    {                                               \
        name##_DremoveItem(list->next, index-1);    \
    }                                               \
    else                                            \
    {                                               \
        name##_Dnode* current = list;               \
        name##_Dnode* nodeToBeRemoved = list->next; \
        name##_Dnode* newNext = nodeToBeRemoved->next;\
        current->next = newNext;                    \
        newNext->previous = current;                \
        free(nodeToBeRemoved);                      \
    }                                               \
}                                                   \
                                                    \
void name##_DchangeValue(name##_Dnode* list, int index, type* newData)\
{                                                   \
    if(index > 0 && list->next == NULL)             \
        return;                                     \
                                                    \
    if(index > 0)                                   \
    {                                               \
        name##_DchangeValue(list->next, index-1, newData);\
    }                                               \
    else                                            \
    {                                               \
        list->data = *newData;                      \
    }                                               \
}                                                   \
                                                    \
void name##_DdestroyLinkedList(name##_Dnode* list)  \
{                                                   \
    if(list->next == NULL)                          \
    {                                               \
        free(list);                                 \
    }                                               \
    else                                            \
    {                                               \
        name##_DdestroyLinkedList(list->next);      \
        free(list);                                 \
    }                                               \
}