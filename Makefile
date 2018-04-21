all: main.c listdir.c cmds.c
	gcc -g -Wall -o directoryExplorer main.c tree.c listdir.c cmds.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf directoryExplorer