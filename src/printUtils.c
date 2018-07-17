#include "printUtils.h"

//Prints the nivel specified of the given three
void printTreeLevel(struct lnode *tree, int level)
{
    printf(" %s\n",tree->value->name );
    if (tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while (aux != NULL) {   
            int i = 0;
            while (i <= level) {
                printf("-");
                i++;
            }
            
            printTreeLevel(aux, level+1);
            aux = aux->next;
        }
    }
}

void printTree(struct lnode *tree)
{
    printTreeLevel(tree, 0);
}



void printTreeLevelFolders(struct lnode *tree, int level)
{
    if (tree->value->is_dir)    
        printf(" %s\n",tree->value->name );

    if (tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while (aux != NULL) {
            if (aux->value->is_dir) {
                int i = 0;
                while(i <= level) {
                    printf("-");
                    i++;
                }
                printTreeLevelFolders(aux, level+1);
            }
            aux = aux->next;
        }
    }
}

void printFoldersOnly(struct lnode *tree)
{
    printTreeLevelFolders(tree,0);
}

//Print the path of all files in the tree
int printTreeFilesRecurr(struct lnode *tree, const char *path, int printed)
{
    if (tree == NULL)
        return printed;

    char newPath[1000] = "";
    strcpy(newPath,path);
    strcat(newPath,tree->value->name);
    if (!tree->value->is_dir) {
        printf("%s\n", newPath);
        printed++;
    }

    if(tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while (aux != NULL) {
            printed = printTreeFilesRecurr(aux, newPath, printed);
            aux = aux->next;
        }
    }
    return printed;
}


void printFilesOnly(struct lnode *tree)
{
    char path[] = "";
    int printed;
    printed = printTreeFilesRecurr(tree,path,0);
    if (printed == 0)
        printf("There is no file in the folder %s.\n",tree->value->name );
}


int printFilesExtOnly(struct lnode *tree, const char *ext, const char *path, int printed)
{

    if (tree == NULL)
        return printed;

    char newPath[1000] = "";
    strcpy(newPath, path);
    strcat(newPath,tree->value->name);

    char *filesExt;
    filesExt = strrchr(tree->value->name, '.');

    if (filesExt != NULL) {
        filesExt++;
        if (strcmp(filesExt, ext) == 0) {
            printf("%s\n", newPath);
            printed++;
        }
    }

    if (tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while(aux != NULL) {
            printed = printFilesExtOnly(aux, ext, newPath,printed);
            aux = aux->next;
        }
    }
    return printed;
}

void filesExtOnly(struct lnode *tree, const char *ext)
{
    char path[] = "";
    int printed;
    printed = printFilesExtOnly(tree, ext, path,0);
    if (printed == 0)
        printf("There is no file with the %s extension.\n", ext);

}

int locateFullReccur(struct lnode *tree, const char *name, const char *path, int printed)
{
    if (tree == NULL)
        return printed;

    char newPath[1000] = "";
    strcpy(newPath, path);
    strcat(newPath,tree->value->name);

    if (strcmp(tree->value->name, name) == 0) {
        printf("%s\n", newPath);
        printed++;
    }

    if (tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while(aux != NULL) {
            printed = locateFullReccur(aux, name, newPath, printed);
            aux = aux->next;
        }
    }
    return printed;

}

void locateFull(struct lnode *tree, const char *name)
{
    char path[] = "";
    int printed;
    printed = locateFullReccur(tree, name, path,0);
    if (printed == 0)
        printf("There is no file called %s.\n",name );

}

int locatePartialRecur(struct lnode *tree, const char *name, const char *path, int printed)
{
    if (tree == NULL)
        return printed;

    char newPath[1000] = "";
    strcpy(newPath, path);
    strcat(newPath,tree->value->name);

    if (strstr(tree->value->name, name) != NULL) {
        printf("%s\n", newPath);
        printed++;
    }

    if (tree->value->children != NULL) {
        struct lnode *aux = malloc(sizeof(struct lnode));
        aux = tree->value->children;
        while(aux != NULL) {
            printed = locatePartialRecur(aux, name, newPath, printed);
            aux = aux->next;
        }
    }
    return printed;
}

void locatePartial(struct lnode *tree, const char *name)
{
    char path[] = "";
    int printed;
    printed = locatePartialRecur(tree, name, path,0);

    if(printed == 0)
        printf("There is no file with the string %s in the name.\n", name);
}

