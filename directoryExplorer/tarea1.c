#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#include <unistd.h>

#include "tree.h"
#include "listdir.h"
#include "cmds.h"

int main(int argc, char *argv[])
{
	struct lnode *a = NULL;

	if (argv[1] != NULL) {
		if (argv[2] == NULL) {
			a = createTreeLimited(argv[1],0);
		} else {
			int depth = atoi(argv[2]);
			if (depth >= 0)
				a = createTreeLimited(argv[1],depth);
			else
				printf("You have to put a positive integer for"
					" the secound parameter.\n");
			// if (depth == 0)
			// 	printf("n");
			// else
			// 	a = createTreeLimited(argv[1],depth);
		}
	}	

	if(a != NULL)
		shell(a);
	else
		printf("The directory couldn't be opened.\n");
	return 0;
}