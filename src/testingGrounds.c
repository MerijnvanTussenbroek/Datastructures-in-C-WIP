//#include "list.h"
//#include "set.h"

#include "testingGrounds.h"

#include "binary_tree_impl.h"

void printList(int* arr);

DEFINE_BINARY_TREE(intBT, int);

int main(){


    printf("\nProgram finished with no problems");
    return 0;
}

void printList(int* arr)
{
    for(int i = 0; i < 16; i++)
    {
        printf("%d\n", arr[i]);
    }
}
