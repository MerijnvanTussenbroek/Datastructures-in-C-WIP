#include "testingGrounds.h"

#include "hashset_impl.h"

DEFINE_HASHSET(test, int);

void printNum(int inputKey);
int compFunc(int a, int b);

int main(){

    test_hashset* set = test_initializehashset(10, compFunc);

    test_addToHashset(set, 0);
    test_addToHashset(set, 1);
    test_addToHashset(set, 2);
    test_addToHashset(set, 3);
    test_addToHashset(set, 4);

    test_iterationFunc(set, printNum);

    int test1 = test_containsHashset(set, 10);
    int test2 = test_containsHashset(set, 1);

    printf("\n%d %d\n", test1, test2);

    int test3 = test_removeFromHashset(set, 10);
    int test4 = test_removeFromHashset(set, 1);

    printf("\n%d %d\n", test1, test2);

    test_iterationFunc(set, printNum);

    test_destroyHashset(set);
    
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


