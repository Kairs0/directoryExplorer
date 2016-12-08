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

//Recursive function for printTree
void printTreeLevel(struct lnode *tree, int level);
//Lists all the files and folders in the tree
void printTree(struct lnode *tree);

//Recursive function for printFoldersOnly
void printTreeLevelFolders(struct lnode *tree, int level);
//Lists all the folders in the tree
void printFoldersOnly(struct lnode *tree);

//Recursive function for printFiles Only
int printTreeFilesRecurr(struct lnode *tree, const char *path, int printed);
//Lists all the files in the tree
void printFilesOnly(struct lnode *tree);


//Recursive function for printing a particular extension
int printFilesExtOnly(struct lnode *tree, const char *ext, const char *path, int printed);
//Lists all the files with a given extension.
void filesExtOnly(struct lnode *tree, const char *ext);

//Recursive function for locating a full name
int locateFullReccur(struct lnode *tree, const char *name, const char *path, int printed);
//Prints the path of the node with the given name
void locateFull(struct lnode *tree, const char *name);

//Recursive function for locating with the partial option
int locatePartialRecur(struct lnode *tree, const char *name, const char *path, int printed);
//Prints all the results
void locatePartial(struct lnode *tree, const char *name);

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
