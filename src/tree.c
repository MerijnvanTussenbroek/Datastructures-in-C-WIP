#include "tree.h"

void destroyNode(treeNode* n);
void foldOverNode(treeNode* n);

tree* initializeTree()
{
    tree* t = malloc(sizeof(tree));

    t->root = NULL;

    return t;
}

treeNode* initializeNode(char* id)
{
    treeNode* node = malloc(sizeof(treeNode));

    node->listLength = 0;
    node->childNodes = NULL;
    node->identifier = id;
    node->type = UNUSED;
    node->fold = NULL;
    node->f = NULL;

    return node;
}

void destroyTree(tree* t)
{
    for(int i = 0; i < t->root->listLength; i++)
    {
        destroyNode(t->root->childNodes[i]);
    }

    free(t);
}

void destroyNode(treeNode* n)
{
    if(n->type == POINTER)
    {
        n->f(n->e);
    }

    for(int i = 0; i < n->listLength; i++)
    {
        destroyNode(n->childNodes[i]);
    }

    free(n);
}

void changeValueInTree(treeNode* node, varType v, ...)
{
    va_list l;

    va_start(l,v);

    if(node->type == POINTER)
        node->f(node->e);

    node->type = v;

    switch(v)
    {
        case INTEGER:
        node->a = va_arg(l, int);
        break;
        case CHAR:
        node->b = va_arg(l, char);
        break;
        case DOUBLE:
        node->c = va_arg(l, double);
        break;
        case FLOAT:
        node->d = (float)va_arg(l, double);
        break;
        case UNUSED:
        node->a = 0;
        break;
        case NOTHING:
        node->a = 0;
        break;
        case POINTER:
        node->e = va_arg(l, void *);
        node->f = va_arg(l, DeallocateFunction);
        break;
        default:
        printf("\nsomething went wrong in changing the value on a node");
        exit(-1);
    }

    va_end(l);
    return;
}

void addSingleNode(treeNode* root, treeNode* newLeaf)
{
    addMoreNodes(root, 1, newLeaf);
}

void addMoreNodes(treeNode* root, int count, ...)
{
    if(count <= 0)
        return;

    va_list l;

    va_start(l, count);

    treeNode** list = root->childNodes;
    int newLength = count + root->listLength;

    treeNode** temp = realloc(list, sizeof(treeNode*) * newLength);

    list = temp;

    for(int i = root->listLength; i < newLength; i++)
    {
        list[i] = va_arg(l, treeNode*);
    }

    va_end(l);
}

void folderFunction(tree* t)
{
    foldOverNode(t->root);
}

void foldOverNode(treeNode* n)
{
    switch (n->type)
    {
    case INTEGER:
        void* intVar = malloc(sizeof(int));
        intVar = &n->a;
        n->fold(intVar);
        free(intVar);
        break;
    case CHAR:
        void* charVar = malloc(sizeof(char));
        charVar = &n->b;
        n->fold(charVar);
        free(charVar);
        break;
    case DOUBLE:
        void* doubleVar = malloc(sizeof(double));
        doubleVar = &n->c;
        n->fold(doubleVar);
        free(doubleVar);
        break;
    case FLOAT:
        void* floatVar = malloc(sizeof(float));
        floatVar = &n->d;
        n->fold(floatVar);
        free(floatVar);
        break;
    case UNUSED:
        printf("\ntrying to fold over an unused node");
        exit(-1);
        break;
    case NOTHING:
        //does nothing
        break;
    case POINTER:
        n->fold(n->e);
        break;
    default:
        printf("Tried folding over a non-existent type of node");
        exit(-1);
        break;
    }

    for(int i = 0; i < n->listLength; i++)
    {
        foldOverNode(n->childNodes[i]);
    }
}
