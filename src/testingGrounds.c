//#include "list.h"
//#include "set.h"

#include "testingGrounds.h"

#include "double_linked_list_impl.h"

DEFINE_DOUBLE_LINKED_LIST(test, int);

void printList(int* arr, int length);
int compare(const int a, const int b);
int comp(const int a, const int b);
void printInteger(int input);

int main(){

    test_DLL* DLL = test_initializeDLL(0);

    test_DaddNewNode(DLL, 1);
    test_DaddNewNode(DLL, 2);
    test_DaddNewNode(DLL, 3);
    test_DaddNewNode(DLL, 4);

    test_DLLIterate(DLL, printInteger);

    printf("\n%d\n", test_DgetSize(DLL));

    test_DremoveItem(DLL, 0);
    test_DremoveItem(DLL, 3);

    test_DLLIterate(DLL, printInteger);

    test_DchangeValue(DLL, 1, 10);

    test_DLLIterate(DLL, printInteger);

    test_DdestroyLinkedList(DLL);
    
    printf("\nProgram finished with no problems");
    return 0;
}

void printList(int* arr, int length)
{
    printf("\n");
    for(int i = 0; i < length; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");
}

void printInteger(int input)
{
    printf("%d\n", input);
}

int compare(const int a, const int b)
{
    if(a < b)
    {
        return 1;
    }
    return 0;
}

int comp(const int a, const int b)
{
    if(a == b)
    {
        return 1;
    }
    return 0;
}
