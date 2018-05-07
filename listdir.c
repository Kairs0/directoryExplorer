#include "listdir.h"

/*
Returns a linked_list of folders and files from the given path
Returns a NULL pointer if:
    - the path is not correct,
    - the path is a filer,
    - the folder is empty.
*/
struct list_node *listdir(const char *path)
{
    DIR *dir = NULL;
    dir = opendir(path);

    if (dir == NULL || isFolderEmpty(dir))
        return NULL;

    struct dirent *pCurrentFile = readdir(dir);

    // define a file default container
    int size = numberElementsFolder(dir);
    struct list_node *pListContainer = NULL;
    pListContainer = malloc(size * sizeof(struct list_node));
    pListContainer->next = NULL;
    pListContainer->name = NULL;

    pCurrentFile = readdir(dir);

    while (pCurrentFile != NULL) {
        //We do not consider the parent folder and the actual folder
        if (strcmp(pCurrentFile->d_name, ".") == 0 || strcmp(pCurrentFile->d_name, "..") == 0) {
            pCurrentFile = readdir(dir);
            continue;
        }

        struct list_node *pNewFile = NULL;
        pNewFile = malloc(sizeof(struct list_node));

        pNewFile->name = malloc(600*sizeof(char)); // potential bug
        strcpy(pNewFile->name, pCurrentFile->d_name);

        /*
        struct list_node *aux = NULL;
        aux = malloc(sizeof(struct list_node));
        (*aux) = (*pListContainer);
        */

        if (pCurrentFile->d_type == DT_DIR) {
            pNewFile->is_dir = 1;
            //We always place the folder at the beginning of the list.
            //But if the file is empty, we put a null pointer
            //as a follower of the new member.

            //INTENT WITH NEW FUNC
            addToHead((*pNewFile), pListContainer);
            //END INTENT

        } else if (pCurrentFile->d_type == DT_REG) {
            pNewFile->is_dir = 0;

            //If there is no file yet in the list, we put it right now.
            //Else we put it at the end of the list
            if (pListContainer->name == NULL) {

                //INTENT WITH NEW FUNC
                addToHead(*pNewFile, pListContainer);
                //END INTENT

                /*
                pListContainer = pNewFile;
                pListContainer->next = NULL;*/
            } else {
                // INTENT WITH NEW FUNC
                addToEnd(*pNewFile, pListContainer);
                //END INTENT

                /*
                // aux = pListContainer;
                while(aux->next != NULL) //SEG FAULT
                    // (*aux) = *(aux->next);
                    aux = aux->next;

                aux->next = pNewFile;*/
            }
        }
        
        pCurrentFile = readdir(dir);
    }
    closedir(dir);
    return pListContainer;
}

struct list_node * create(char * name, int isDir, struct list_node * next) {
    struct list_node * newNode = malloc(sizeof(struct list_node));
    strcpy(newNode->name, name);
    newNode->is_dir = isDir;
    newNode->next = next;
    return newNode;
}

void addToHead(struct list_node value, struct list_node * pHead) {
    struct list_node * newNode = malloc(sizeof(struct list_node));
    (*newNode) = value;
    newNode->next = pHead;
    pHead = newNode;
}

void addToEnd(struct list_node value, struct list_node * pHead) {
    struct list_node * newNode = malloc(sizeof(struct list_node));
    (*newNode) = value;
    newNode->next = NULL;

    struct list_node * cursor = pHead;
    while (cursor->next != NULL)
        cursor = cursor->next;

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