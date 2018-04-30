#ifndef __PRINT_UTILS
#define __PRINT_UTILS

#include <stdlib.h>
#include <stdio.h>

// #include "listdir.h"
#include "tree.h"


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

#endif