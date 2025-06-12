//#include "list.h"
//#include "set.h"

#include "testingGrounds.h"

#include "stack_impl.h"

DEFINE_STACK(test, int);


void printList(int* arr);

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
