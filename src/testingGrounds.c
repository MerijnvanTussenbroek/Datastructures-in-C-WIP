//#include "list.h"
//#include "set.h"
#include "linked_list.h"
#include "stack.h"

//DEFINE_LINKED_LIST(int, int);
DEFINE_STACK(int, int);

void testStack();

int main(){

    int x = 5;
    int y = 7;
    int z = 0;

    int a = 6;
    int b = 3;
    int c = 10;

    int_node* head = int_initializateLinkedList(&x);
    printf("Initialized list\n");
    int_addNewNode(head, &y);
    int_addNewNode(head, &z);
    int_addNewNode(head, &a);
    int_addNewNode(head, &b);
    int_addNewNode(head, &c);

    printf("added data\n");
    
    int_LLresult result = int_retrieveData(head, 4);
    printf("%d \n", result.value);

    result = int_retrieveData(head, 3);
    printf("%d \n", result.value);

    a = 69;
    printf("%d \n", result.value);  

    a = 70;
    int_changeValue(head, 3, &a);

    result = int_retrieveData(head, 3);
    printf("%d \n", result.value);
    
    int_removeItem(head, 3);

    result = int_retrieveData(head, 3);
    printf("%d \n", result.value);

    result = int_retrieveData(head, 0);
    printf("%d \n", result.value);

    int_removeItem(head, 0);

    result = int_retrieveData(head, 0);
    printf("%d \n", result.value);

    printf("\n\n\n");
    testStack();

    printf("\nProgram finished with no problems");
    return 0;
}

void testStack()
{
    int x = 5;
    int_stack* stack = int_initializeStack(&x);

    
}
