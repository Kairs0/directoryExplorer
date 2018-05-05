all: main.c listdir.c cmds.c
	gcc -g -Wall -o directoryExplorer main.c tree.c listdir.c cmds.c printUtils.c

graph:
	gcc -pg main.c tree.c listdir.c cmds.c printUtils.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf directoryExplorerGraph
	rm -rf directoryExplorer
	rm -rf *.stackdump