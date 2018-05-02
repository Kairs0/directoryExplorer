#include "listdir.h"

//Returns a linked_list of folders and files from the path given
//Returns a NULL pointer if this the path is a file or is not correct
struct list_node *listdir(const char *path)
{
    DIR *dir = NULL;
    dir = opendir(path);

    //Returns a NULL pointer if the path is not correct
    if (dir == NULL) {
        //Path isn't correct or is the path of a file
        return NULL;
    } else {
        struct dirent *actualfile = NULL;
        actualfile = readdir(dir);

        struct list_node *files = NULL;
        files = malloc(sizeof(struct list_node));
        files->next = NULL;//TESSSST
        files->name = NULL;

        //If the folder is empty, there are only two elements inside
        //We return a NULL pointer if the folder is empty.
        int compt = 0;
        while (actualfile != NULL) {
            compt++;
            actualfile = readdir(dir);
        }

        if (compt == 2) {
            //The folder is empty
            return NULL;
        }

        //We go back to the beginning the stream of reading
        rewinddir(dir);
        actualfile = readdir(dir);

        while (actualfile != NULL) {
            //We do not consider the parent folder and the actual folder           
            if (strcmp(actualfile->d_name,".") != 0 && strcmp(actualfile->d_name,"..") != 0) {
                struct list_node *new = NULL;
                new = malloc(sizeof(struct list_node));

                new->name = malloc(200*sizeof(char));
                strcpy(new->name,actualfile->d_name);

                struct list_node *aux = NULL;
                // aux = malloc(sizeof(struct list_node));
                aux = files;

                if (actualfile->d_type == DT_DIR) {
                    new->is_dir = 1;
                    //We always place the folder at the beginning of the list.
                    //But if the file is empty, we put a null pointer
                    //as a follower of the new member.
                    if(files->name == NULL)
                        new->next = NULL;             
                    else
                        new->next = files;
                    files = new ;
                } else if (actualfile->d_type == DT_REG) {
                    new->is_dir = 0;

                    //If there is no file yet in the list
                    if (files->name == NULL) {
                        files = new;
                        files->next = NULL;
                    } else {
                        aux = files;
                        while(aux->next != NULL) //SEG FAULT
                            aux = aux->next;
                        aux->next = new;
                    }
                }
            }
            actualfile = readdir(dir);
        }
        closedir(dir);
        return files;
    }
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