#ifndef __CMDS
#define __CMDS
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include "tree.h"

//Typedef pointer to function
typedef void(*cmd_t)(struct lnode*, char **);

//Set of functions used for the interface
char **splitLine(char *line);
char *readLine();
void shell(struct lnode *tree);

//set of functions used to do operations with the three
void list(struct lnode* tree, char **argv);
void fext(struct lnode* tree, char **argv);
void locate(struct lnode* tree, char **argv);

#endif