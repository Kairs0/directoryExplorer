#ifndef __LINKED_LIST
#define __LINKED_LIST
#include <dirent.h>

struct list_node
{
    char *name;
    int is_dir;
    struct list_node *next;
};

typedef struct list_node List_Node;

struct list_node *listdir(const char *path);
void clean_dirlist(struct list_node **list);

int isFolderEmpty(DIR * dir);
int numberElementsFolder(DIR * dir);

struct list_node * create(char * name, int isDir, struct list_node * next);
void addToHead(struct list_node value, struct list_node ** pHead);
void addToEnd(struct list_node value, struct list_node * pHead);

void printdir(struct list_node *list);
void suppr(struct list_node **list);

void eraseDataNode(List_Node *node);
void freeList(List_Node * head);

#endif