#include "cmds.h"
//We define what separators we will use to seperate the words in a command
#define delim " \t\r\n\a"

//The shell function will display the interface.
void shell(struct lnode *tree)
{
	char *line;
	char **args;
	int open = 1;

	//List of names of the functions
	const char *cmds[] = {"list","fext","locate"};

	cmd_t actions[3];
	actions[0] = &list;
	actions[1] = &fext;
	actions[2] = &locate;


	printf("\nWelcome to the managing files interface.\n"
		"The directory was successfuly opened, and you "
		"can use the following commands "
		": \n\nlist [filonly|dironly]\nfext <ext>\nlocate "
		"<pattern> (full|partial)\nquit\n\n");

	while (open == 1) {
		printf("> ");
		line = readLine();
		args = splitLine(line);

		int j = 3; //Number of commands disponibles
		int i = 0;

		for (i = 0; i<j; i++) {
			if(strcmp(cmds[i],args[0]) == 0)
				actions[i](tree,args);
		}

		if(strcmp(args[0],"quit") == 0)
			open = 0;
	}
}

//Get the line the user will type
char *readLine()
{
	char *line = NULL;
	size_t sizeBuffer = 0;
	getline(&line,&sizeBuffer,stdin);
	return line;
}

//split a line in differents words
char **splitLine(char *line)
{
	int sizeBuffer = 64;
	int position = 0;
	char ** tokens = malloc(sizeBuffer*sizeof(char*));
	char *token;

	token = strtok(line, delim);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		token = strtok(NULL, delim);
	}

	tokens[position] = NULL;
	return tokens;
}

//The list function
void list(struct lnode* tree, char **argv)
{
	if (argv[1] == NULL)
		printTree(tree);
	else {
		if (strcmp(argv[1],"fileonly") == 0)
			printFilesOnly(tree);
		else if (strcmp(argv[1],"dironly") == 0)
			printFoldersOnly(tree);
		else
			printf("Wrong argument. To use the \"list\" command, you"
			" can either put \"dironly\" or \"fileonly\" or "
			"nothing as parameters.\n");
	}
}

//The filter function
void fext(struct lnode* tree, char **argv)
{
	if (argv[1] == NULL)
		printf("You should put in argument an extension.\n");
	else
		filesExtOnly(tree,argv[1]);
}

//The locate function
void locate(struct lnode* tree, char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL) {
		printf("You should specify in first parameter the string that will "
			"be used to search, and \"full\" or \"partial\" as the second "
			"parameter. \n");
	} else {
		if (strcmp(argv[2],"full") == 0)
			locateFull(tree, argv[1]);
		else if (strcmp(argv[2],"partial") == 0)
			locatePartial(tree, argv[1]);
		else
			printf("You should specify \"full\" or \"partial\" for the "
				"second parameter\n");
	}
}