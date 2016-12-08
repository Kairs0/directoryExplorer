#ifndef __LINKED_LIST
#define __LINKED_LIST
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

struct list_node *listdir(const char *path);
void clean_dirlist(struct list_node **list);

void printdir(struct list_node *list);
void suppr(struct list_node **list);


struct list_node
{
	char *name;
	int is_dir;
	struct list_node *next;
};

#endif