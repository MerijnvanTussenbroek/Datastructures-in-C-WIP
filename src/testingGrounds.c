#include "list.h"
#include "set.h"

DEFINE_SET(char, char);

int cmp(const char* a, const char* b);

int main()
{
    char_set* set = char_setCreate(4);
    char_addToSet(set, 'a', cmp);
    //char_addToSet(set, 'b', cmp);
    //char_addToSet(set, 'c', cmp);
    //char_addToSet(set, 'd', cmp);
    printf("adding second a %d\n", set->size);
    char_addToSet(set, 'a', cmp);
    char_addToSet(set, 'b', cmp);
    printf("adding second a %d\n", set->size);


    char_deleteSet(set);

    printf("Program finished with no problems");
    return 0;
}

int cmp(const char* a, const char* b)
{
    printf("%c, %c \n", *a, *b);
    if(*a == *b)
    {
        return 2;
    }

    return 0;
}