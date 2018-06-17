#include <stdio.h>
#include <stdlib.h>

// #include "tests.h"
#include "listdir.h"

int test_freeList();
int test_listdir();

int main(int argc, char const *argv[])
{
    //struct list_node *result = listdir("/home/kairs0/Documents");

    test_freeList();
    test_listdir();
    // clean_dirlist(&result);


    return 0;
}

int test_listdir() {
    int sucess = 1;
    List_Node * result = listdir("/home/kairs0/Documents/sandbox");
    freeList(result);
    return sucess;
}

int test_freeList() {
    int sucess = 1;
    List_Node * test = calloc(1, sizeof(List_Node));
    test->name = malloc(132 * sizeof(char));
    List_Node * test1 = calloc(1, sizeof(List_Node));
    test1->name = malloc(2131 * sizeof(char));
    test->next = test1;

    List_Node * test2 = calloc(1, sizeof(List_Node));
    test1->next = test2;

    freeList(test);
    return sucess;
}