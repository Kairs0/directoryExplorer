#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// #include "tests.h"
#include "listdir.h"

int test_freeList();
int test_listdir();
int test_reeaddir();

#define LAUNCH_TEST(function) do { if(function()) \
    printf("%-15s : sucess\n", #function); \
    else printf("%-15s : failed\n", #function);} while(0);


int main(int argc, char const *argv[])
{
    LAUNCH_TEST(test_listdir);
    LAUNCH_TEST(test_freeList);

    LAUNCH_TEST(test_reeaddir);
    return 0;
}

int test_reeaddir() {
    int success = 1;
    DIR * dir = NULL;
    dir = opendir("/home/kairs0/Documents/sandbox");

    if (dir == NULL || isFolderEmpty(dir))
        return 0;

    struct dirent * pCurrentFile = readdir(dir);

    while (pCurrentFile != NULL) {
        printf("%s\n", pCurrentFile->d_name);
        pCurrentFile = readdir(dir);
    }


    return success;
}

int test_listdir() {
    int success = 1;
    List_Node * result = listdir("/home/kairs0/Documents/sandbox");

    if (strcmp(result->name, "test") != 0) {
        success = 0;
    }

    if (strcmp(result->next->name, "testSleep.c") != 0)
        success = 0;

    freeList(result);
    return success;
}

int test_freeList() {
    int success = 1;
    List_Node * test = calloc(1, sizeof(List_Node));
    test->name = malloc(132 * sizeof(char));
    List_Node * test1 = calloc(1, sizeof(List_Node));
    test1->name = malloc(2131 * sizeof(char));
    test->next = test1;

    List_Node * test2 = calloc(1, sizeof(List_Node));
    test1->next = test2;

    freeList(test);
    return success;
}