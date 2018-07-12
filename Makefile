TESTSOURCES = listdir.c tests.c
SOURCES = tree.c main.c listdir.c cmds.c printUtils.c
TRASH = *.out *.stackdump *.o
DEFAULTFLAGS = -g -Wall
GRAPHFLAGS = -pg
CC = gcc

all:
	$(CC) $(DEFAULTFLAGS) -o directoryExplorer.out $(SOURCES)

graph:
	$(CC) $(GRAPHFLAGS) $(SOURCES)

test:
	$(CC) $(DEFAULTFLAGS) -o binTest.out $(TESTSOURCES)

clean:
	rm -f $(TRASH)

mrproper: clean
	printf "\33c"
