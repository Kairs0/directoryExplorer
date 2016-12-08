#include "tree.h"

/**
Creates an unique node with the specified path.
If the path is incorrect, will return a NULL pointer
*/
struct lnode *createOneNode(const char *path)
{
	char *localPath = strdup(path);

	struct lnode *newNode = NULL;
	newNode = malloc(sizeof(struct lnode));
	newNode->next = NULL;
	struct tnode *newValue = NULL;
	newValue = malloc(sizeof(struct tnode));
	newNode->value = newValue;
	newNode->value->children = NULL;

	//erase the last caracter in the path if it's "/"
	int i = strlen(localPath);
	if (i > 0 && localPath[i-1] == '/') {
		i--;
		localPath[i] = '\0';
	}

	//Gets the name of the directory or folder
	char *nameFile;
	nameFile = strrchr(localPath,'/') + 1;

	DIR *dir = NULL;
	dir = opendir(path);
	if (dir != NULL) {
		//Add "/" as the last character if it's a folder
		char slash[] = "/";
		strcat(nameFile,slash);

		newNode->value->is_dir = 1;
		newNode->value->name = strdup(nameFile);		
	} else {
		//Path could be either a wrong path or the path of a simple file.
		FILE *file1 = NULL;
		file1 = fopen(path,"r");
		if (file1 != NULL) {
			//path is the path of a simple file
			newNode->value->is_dir = 0;
			newNode->value->name = strdup(nameFile);
			fclose(file1);			
		} else {
			//path specified is incorrect
			return NULL;
		}
	}
	closedir(dir);	
	return newNode;
}

/**
This functions creates a tree with only one level of depth with the specified path.
Wil return a NULL pointer if the path is incorrect
*/
struct lnode *createTreeOneLevel(const char *path)
{
	struct lnode *newNode = NULL;
	newNode = malloc(sizeof(struct lnode));
	//We start to get the first node
	newNode = createOneNode(path);

	if (newNode == NULL)
		return NULL;

	struct list_node *listChildren = listdir(path);

	if (listChildren != NULL){
		struct lnode *gettingChild = NULL;
		gettingChild = malloc(sizeof(struct lnode));
		gettingChild->next = NULL;
		struct tnode *gettingChildValue = NULL;
		gettingChildValue = malloc(sizeof(struct tnode));

		gettingChildValue->name = strdup(listChildren->name);
		gettingChildValue->is_dir = listChildren->is_dir;
		gettingChild->value = gettingChildValue;

		//If we're dealing with a folder, we put back the "/" after the name
		if (listChildren->is_dir) {
			char slash[] = "/";
			strcat(gettingChildValue->name, slash);
		}

		listChildren = listChildren->next;

		while(listChildren != NULL) {
			//Creating new node with values those of the children
			struct lnode *getNextChild = NULL;
			getNextChild = malloc(sizeof(struct lnode));

			getNextChild->next = NULL;

			struct tnode *getNextChildValue = NULL;
			getNextChildValue = malloc(sizeof(struct tnode));

			getNextChildValue->name = strdup(listChildren->name);
			getNextChildValue->is_dir = listChildren->is_dir;
			if (listChildren->is_dir) {
				char slash[] = "/";
				strcat(getNextChildValue->name, slash);
			}

			getNextChild->value = getNextChildValue;

			struct lnode *aux = NULL;
			aux = malloc(sizeof(struct lnode));
			aux = gettingChild;

			while (aux->next != NULL)
				aux = aux->next;

			aux->next = getNextChild;

			listChildren = listChildren->next;
		}
		newNode->value->children = gettingChild;
	}
	clean_dirlist(&listChildren);
	return newNode;
}


//Will put the given node at the end of the list of followers of a node
void putAsANext(struct lnode *target, struct lnode *newNext)
{
	if (target != NULL && newNext != NULL) {
		struct lnode *aux = NULL;
		aux = malloc(sizeof(struct lnode));
		aux = target;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = newNext;
	}
}

//Will put the given node a the end of the list of children of a target node
void putAsAChild(struct lnode *target, struct lnode *child)
{
	if (target != NULL && child != NULL) {
		if(target->value->children == NULL)
			target->value->children = child;
		else
			putAsANext(target->value->children, child);
	}
}

//Create an tree (with no limit of depth)
struct lnode *createTree(const char *path)
{
	struct lnode *b = NULL;
	b = malloc(sizeof(struct lnode));
	b = createTreeOneLevel(path);

	struct lnode *a = malloc(sizeof(struct lnode));
	a = createOneNode(path);

	if (b->value->children == NULL)
		return a;
	else {
		struct lnode *aux = NULL;
		aux = malloc(sizeof(struct lnode));
		aux = b->value->children;
		while(aux != NULL) {
			char dest[600];//assuming that the length of a path is under 600
			strcpy(dest, path);

			int i = strlen(dest);
			if (i > 0 && dest[i-1] != '/') {
				char slash[] = "/";
				strcat(dest, slash);
			}
			strcat(dest, aux->value->name);
			putAsAChild(a,createTree(dest));
			aux=aux->next;
			}
		return a;
	}
}

//Creates the tree with the specified level of depth
struct lnode *createTreeLimited(const char *path, int level)
{
	if (level < 0) {
		return NULL;
	} else if (level == 0) {
		struct lnode *b = NULL;
		b = malloc(sizeof(struct lnode));
		b = createTreeOneLevel(path);

		if(b == NULL)
			return NULL;

		struct lnode *a = malloc(sizeof(struct lnode));
		a = createOneNode(path);

		if (b->value->children == NULL) {
			return a;
		} else {
			struct lnode *aux = NULL;
			aux = malloc(sizeof(struct lnode));
			aux = b->value->children;
			while (aux != NULL) {
					char dest[600];
					strcpy(dest, path);
					int i = strlen(dest);
					if(i > 0 && dest[i-1] != '/') {
						char slash[] = "/";
						strcat(dest, slash);
					}

					strcat(dest, aux->value->name);
					putAsAChild(a,createTree(dest));
						
					aux=aux->next;
				}
			return a;
		}
	} else if (level == 1) {
		struct lnode *a = NULL;
		a = malloc(sizeof(struct lnode));
		a = createOneNode(path);
		return a;
	} else if (level == 2) {
		struct lnode *a = NULL;
		a = malloc(sizeof(struct lnode));
		a = createTreeOneLevel(path);
		return a;
	} else {
		struct lnode *b = NULL;
		b = malloc(sizeof(struct lnode));
		b = createTreeOneLevel(path);

		struct lnode *a = malloc(sizeof(struct lnode));
		a = createOneNode(path);

		if (b->value->children == NULL) {
			return a;
		} else {
			struct lnode *aux = NULL;
			aux = malloc(sizeof(struct lnode));
			aux = b->value->children;
			while(aux != NULL) {
				char dest[600];
				strcpy(dest, path);

				int i = strlen(dest);
				if (i > 0 && dest[i-1] != '/') {
					char slash[] = "/";
					strcat(dest,slash);
				}

				strcat(dest, aux->value->name);
				putAsAChild(a, createTreeLimited(dest,level-1));

				aux = aux->next;
			}
		return a;
		}
	}
}



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
			printed = printTreeFilesRecurr(aux,newPath,printed);
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

