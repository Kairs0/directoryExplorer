#ifndef __TREE
#define __TREE
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#include "listdir.h"

//Set of intermediates functions used in the createdTreeLimited fonction
struct lnode *createOneNode(const char *path);
struct lnode *createTreeOneLevel(const char *path);
void putAsANext(struct lnode *target, struct lnode *next);
void putAsAChild(struct lnode *target, struct lnode *child);
struct lnode *createTree(const char *path);

//Function used in the program to generate the tree
struct lnode *createTreeLimited(const char *path, int level);

//Structure of the tree
struct lnode
{
    struct tnode *value;
    struct lnode *next;
};

struct tnode
{
    char *name;
    int is_dir;
    struct lnode *children;
};

#endif
