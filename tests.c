#include <stdio.h>
#include <stdlib.h>

// #include "tests.h"
#include "listdir.h"

int main(int argc, char const *argv[])
{
    //struct list_node *result = listdir("/home/kairs0/Documents");

    List_Node * test = malloc(sizeof(List_Node));

    test->name = malloc(132 * sizeof(char));

    List_Node * test1 = malloc(sizeof(List_Node));

    test1->name = malloc(2131 * sizeof(char));

    test->next = test1;

    freeList(test);


    // clean_dirlist(&result);


    return 0;
}