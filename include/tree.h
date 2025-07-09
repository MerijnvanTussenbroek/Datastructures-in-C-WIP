#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//this tree is specifically for ASTs 

typedef enum varType varType;
typedef enum varType
{
    INTEGER,
    CHAR,
    DOUBLE,
    FLOAT,
    UNUSED,
    NOTHING,
    END, // this is specifically used as a sentinal value when working with the "addingNodes" function
    POINTER //anything but one of the top 7
};

typedef void (*DeallocateFunction)(void *);
typedef void (*FolderFunc)(void *);

typedef struct treeNode treeNode;
typedef struct treeNode          
{                                   
    int index;                      
    char* identifier;
    DeallocateFunction f;
    FolderFunc fold;
    varType type;    
    union 
    {
        int a;
        char b;
        double c;
        float d;
        void* e;
    };
    int listLength;
    treeNode** childNodes;    
};

typedef struct tree tree;
typedef struct tree          
{                
    treeNode* root;                     
};                                  
                                    
tree* initializeTree();
treeNode* initializeNode(char* id);
void destroyTree(tree* t);
void addSingleNode(treeNode* root, treeNode* newLeaf);
void addMoreNodes(treeNode* root, int count, ...);
void changeValueInTree(treeNode* node, varType v, ...);
void folderFunction(tree* t);