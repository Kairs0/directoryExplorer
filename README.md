# Directory Explorer

_Reinventing the wheel._

## Features

- Display tree of folders/files from any given path.
- Search for files or folders within a tree.
- Search for files with given extension.

## Makefile

- `make(all)` : generate executable
- `make clean` : clear the folder from object files
- `make mrproper` : clean and remove executable file

## Valgrind use

` valgrind --leak-check=full --track-origins=yes ./binTest`