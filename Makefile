TESTSOURCES = src/listdir.c tst/tests.c
SOURCES = src/tree.c src/main.c src/listdir.c src/cmds.c src/printUtils.c
TRASH = *.out *.stackdump *.o
DEFAULTFLAGS = -g -Wall
GRAPHFLAGS = -pg
OUT_ALL = -o directoryExplorer.out
OUT_TEST = -o binTest.out
OUT_GRAPH = -o binGraph.out
CC = gcc

all:
	$(CC) $(DEFAULTFLAGS) $(OUT_ALL)  $(SOURCES)

graph:
	$(CC) $(GRAPHFLAGS) $(OUT_GRAPH)  $(SOURCES)

test:
	$(CC) $(DEFAULTFLAGS) $(OUT_TEST) $(TESTSOURCES)

clean:
	rm -f $(TRASH)

mrproper: clean
	printf "\33c"
