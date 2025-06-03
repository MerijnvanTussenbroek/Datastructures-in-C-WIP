//#include "list.h"
//#include "set.h"
#include "testingGrounds.h"

#include "stack_impl.h"

DEFINE_STACK(stack, int);

int main(){

    int x = 5;
    int y = 7;
    int z = 0;

    int a = 6;
    int b = 3;
    int c = 10;

    stack_node* LL = stack_initializeLinkedList(x);

    stack_insertNewNodeToLL(&LL, y, 0);
    stack_insertNewNodeToLL(&LL, z, 0);
    stack_insertNewNodeToLL(&LL, a, 0);
    stack_insertNewNodeToLL(&LL, b, 0);
    stack_insertNewNodeToLL(&LL, c, 0);

    stack_GraphResult result = stack_retrieveDataFromLL(LL, 0);

    stack_removeItemFromLL(&LL, 0);

    printf("\n%d", result.value);

    result = stack_retrieveDataFromLL(LL, 0);

    stack_removeItemFromLL(&LL, 0);

    printf("\n%d", result.value);
    result = stack_retrieveDataFromLL(LL, 0);

    stack_removeItemFromLL(&LL, 0);

    printf("\n%d", result.value);


    stack_stack* stack = stack_initializeStack(x);
    stack_push(stack, y);
    stack_push(stack, z);

    stack_push(stack, a);
    stack_push(stack, b);
    stack_push(stack, c);

    stack_GraphResult result2 = stack_pop(stack);

    if(result2.success == 1)
    {
        printf("%d", result2.value);
    }
    
    result2 = stack_pop(stack);

    if(result2.success == 1)
    {
        printf("%d", result2.value);
    }

    result2 = stack_pop(stack);

    if(result2.success == 1)
    {
        printf("%d", result2.value);
    }

    printf("\nProgram finished with no problems");
    return 0;
}
