#include "testingGrounds.h"

#include "heap_impl.h"

DEFINE_HEAP(test, int);

void printNum(int inputKey);
int compFunc(int a, int b);

int main(){

    
    
    printf("\nProgram finished with no problems");
    return 0;
}


void printNum(int inputKey)
{
    printf("%d", inputKey);
}

int compFunc(int a, int b)
{
    if(a == b)
    {
        return 1;
    }
    return 0;
}


