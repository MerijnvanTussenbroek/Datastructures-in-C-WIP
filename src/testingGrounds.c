#include "testingGrounds.h"

#include "hashmap_impl.h"

DEFINE_HASHMAP(test, int, int);

void printNum(int inputKey, int inputValue);
int compFunc(int* a, int* b);

int main(){

    test_hashmap* map = test_initializehashmap(10);

    int x = 1;
    int y = 1;

    test_addToHashmap(map, &x, &y, sizeof(int));

    x = 2;
    y = 2;

    test_addToHashmap(map, &x, &y, sizeof(int));

    x = 3;
    y = 3;

    test_addToHashmap(map, &x, &y, sizeof(int));

    x = 4;
    y = 4;

    test_addToHashmap(map, &x, &y, sizeof(int));

    x = 5;
    y = 5;

    test_addToHashmap(map, &x, &y, sizeof(int));

    test_iterationFunc(map, printNum);

    printf("\n\n");

    //int test1 = test_containsHashmap1(map, 1, compFunc);
    //int test2 = test_containsHashmap2(map, 1, compFunc);

   // printf("\n%d %d\n", test1, test2);

    x = 3;

    test_specialNode t = test_searchBasedOnKey(map, &x, compFunc);
    test_specialNode t4 = test_searchBasedOnValue(map, &x, compFunc);
    x = 10;
    test_specialNode t2 = test_searchBasedOnKey(map, &x, compFunc);
    test_specialNode t3 = test_searchBasedOnValue(map, &x, compFunc);

    int test = test_removeFromHashmap1(map, &x, compFunc);

    x = 3;

    int test2 = test_removeFromHashmap1(map, &x, compFunc);

    printf("removing m%d %d\n\n", test, test2);

    test_iterationFunc(map, printNum);

    printf("\n%d %d\n", t.theKey, t.theValue);
    printf("\n%d %d\n", t2.theKey, t2.theValue);
    printf("\n%d %d\n", t3.theKey, t3.theValue);
    printf("\n%d %d\n", t4.theKey, t4.theValue);

    x = 3;
    y = 3;

    test_addToHashmap(map, &x, &y, sizeof(int));

    printf("\n\n");

    test = test_removeFromHashmap2(map, &x, compFunc);
    x = 10;
    test2 = test_containsHashmap2(map, &x, compFunc);

    printf("\n\nremoving m%d %d\n\n", test, test2);

    test_iterationFunc(map, printNum);

    test_destroyHashmap(map);
    
    printf("\nProgram finished with no problems");
    return 0;
}


void printNum(int inputKey, int inputValue)
{
    printf("%d %d", inputKey, inputValue);
}

int compFunc(int* a, int* b)
{
    if(*a == *b)
    {
        return 1;
    }
    return 0;
}


