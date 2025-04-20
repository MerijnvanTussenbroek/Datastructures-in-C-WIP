#include "list.h"

DEFINE_LIST(int, int);

int main()
{
    printf("Begin initializing testing grounds\n");
    int_list* list = int_listCreate(5);

    printf("Initialized datastructure, adding in data\n");

    int_changeInList(list, 5, 0);
    int_changeInList(list, 5, 1);
    int_changeInList(list, 5, 2);
    int_changeInList(list, 5, 3);
    int_changeInList(list, 5, 4);

    int_addToList(list, 6);
    int_addToList(list, 6);
    int_addToList(list, 6);
    int_addToList(list, 6);
    int_addToList(list, 6);
    int_addToList(list, 6);

    printf("Begin trying to retrieve data from datastructure\n");

    int x = int_retrieveFromList(list, 8);
    int y = int_retrieveFromList(list, 10);
    printf("%d %d \n", x, y);

    int_deleteList(list);

    printf("Program finished with no problems");
    return 0;
}