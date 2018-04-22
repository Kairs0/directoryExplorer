#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#include <unistd.h>

#include "tree.h"
#include "listdir.h"
#include "cmds.h"

#define NO_PATH "No path provided."
#define COND_SEC_INT "Second parameter must be positive integer."
#define IO_ERR "The directory couldn't be opened."

int main(int argc, char *argv[])
{
    struct lnode *a = NULL;

    if (argv[1] == NULL) {
        printf("%s %s\n", NO_PATH, IO_ERR);
        return -1;
    }

    if (argv[2] == NULL) {
        a = createTreeLimited(argv[1], 0);
    } else {
        int depth = atoi(argv[2]);
        if (depth < 0)
            printf("%s\n", COND_SEC_INT);
        else 
            a = createTreeLimited(argv[1], depth);
    }

    if (a != NULL)
        shell(a);
    else
        printf("%s\n", IO_ERR);
    return 0;
}