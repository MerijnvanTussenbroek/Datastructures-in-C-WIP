//#include "list.h"
//#include "set.h"

#include "testingGrounds.h"

#include "graph_impl.h"

DEFINE_GRAPH(test, int);


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
