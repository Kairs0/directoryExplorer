#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "listdir.h"

/*
Returns a linked list of folders and files from the given path
Returns a NULL pointer if:
    - the path is not correct,
    - the path is a file,
    - the folder is empty.
*/
struct list_node * listdir(const char *path)
{
    DIR * dir = NULL;
    dir = opendir(path);

    if (dir == NULL || isFolderEmpty(dir))
        return NULL;

    struct dirent * pCurrentFile = readdir(dir);

    // int size = numberElementsFolder(dir);
    struct list_node * pListContainer = NULL;

    pCurrentFile = readdir(dir);

    int counterElementsList = 0;

    while (pCurrentFile != NULL) {
        //We do not consider the parent folder and the current folder
        if (strcmp(pCurrentFile->d_name, ".") == 0 || strcmp(pCurrentFile->d_name, "..") == 0) {
            pCurrentFile = readdir(dir);
            continue;
        }

        struct list_node *pNewFile = NULL;
        pNewFile = calloc(1, sizeof(struct list_node)); 

        pNewFile->next = NULL;

        int len_name = strlen(pCurrentFile->d_name);
        pNewFile->name = calloc(len_name + 1, sizeof(char));
        strcpy(pNewFile->name, pCurrentFile->d_name);

        if (pCurrentFile->d_type == DT_DIR) {
            pNewFile->is_dir = 1;
            //We always place folders at the beginning of the list.
            if (counterElementsList == 0) {
                pListContainer = create(pCurrentFile->d_name, 1, NULL);
                free(pNewFile->name); //free name now because not used in the linked list (just its value)
            }
            else {
                addToHead((*pNewFile), &pListContainer);
            }

            counterElementsList++;

        } else if (pCurrentFile->d_type == DT_REG) {
            pNewFile->is_dir = 0;
            if (counterElementsList == 0) {
                pListContainer = create(pCurrentFile->d_name, 0, NULL);
                free(pNewFile->name);
            }
            else {
                addToEnd(*pNewFile, pListContainer);
            }

            counterElementsList++;
        }
        free(pNewFile);
        pCurrentFile = readdir(dir);
    }
    closedir(dir);
    return pListContainer;
}

struct list_node * create(char * name, int isDir, struct list_node * next) {
    struct list_node * newNode = malloc(sizeof(struct list_node)); //TODO
    size_t nameLen = strlen(name);
    newNode->name = malloc(nameLen * sizeof(char) + 1);
    strcpy(newNode->name, name); //TODO check size
    newNode->is_dir = isDir;
    newNode->next = next;
    return newNode;
}

void addToHead(struct list_node value, struct list_node ** pHead) {
    struct list_node * newNode = malloc(sizeof(struct list_node));
    (*newNode) = value;
    newNode->next = *pHead;
    *pHead = newNode;
}

void addToEnd(struct list_node value, struct list_node * pHead) {
    struct list_node * newNode = malloc(sizeof(struct list_node));
    (*newNode) = value;
    newNode->next = NULL;

    struct list_node * cursor = pHead;
    while (cursor->next != NULL)
        cursor = cursor->next;

    // cursor->next = malloc(sizeof(struct list_node));
    cursor->next = newNode;
}

int numberElementsFolder(DIR * dir) {
    struct dirent * file = NULL;
    file = readdir(dir);
    int c = 0;
    while (file != NULL) {
        c++;
        file = readdir(dir);
    }
    rewinddir(dir);
    return c - 2;
}

int isFolderEmpty(DIR * dir) {
    // If the folder is empty, there are only two elements inside ('.' and '..')
    struct dirent *file = NULL;
    file = readdir(dir);
    int c = 0;
    while (file != NULL) {
        c++;
        file = readdir(dir);
    }
    rewinddir(dir);
    return c == 2;
}

//Prints the names of folders/files in the given linked list.
void printdir(struct list_node *list)
{
    printf("\n");
    struct list_node *aux = NULL;
    aux = list;
    while (aux != NULL) {
        if (aux->is_dir)
            printf("%s/ \n",aux->name);
        else
            printf("%s\n",aux->name);
        aux = aux->next;
    }
}

void freeList(List_Node * head){
    List_Node * aux = NULL;
    aux = head;
    while (aux != NULL) {
        eraseDataNode(aux);
        aux = aux->next;
    }
    aux = head;
    while (aux != NULL) {
        List_Node * temp = aux;
        aux = temp->next;
        free(temp);
    }
    // free(head);
}

void eraseDataNode(List_Node *node){
    free(node->name);
}

//Erase a given node
//We do not erase list->is_dir : hence it was created
//automatically, it is not in the heap
void suppr(struct list_node **list)
{
    if (list !=NULL) {
        if (*list != NULL) {
            struct list_node **aux = list;
            free((**aux).name);
            (**aux).name = NULL;
            free(*aux);
            *aux = NULL;
        }
    }
}

//Erase all nodes of a given list of the heap memory
void clean_dirlist(struct list_node **list)
{
    if (list != NULL) {
        if (*list != NULL) {
            struct list_node **aux1 = NULL;
            aux1 = malloc(sizeof(struct list_node));
            aux1 = list;

            struct list_node **aux2 = NULL;
            aux2 = malloc(sizeof(struct list_node));
            aux2 = &((**aux1).next);

            while(*aux1 != NULL) {
                suppr(aux1);
                aux1 = aux2;
                aux2 = &((**aux1).next);
            }
        }
    }
}