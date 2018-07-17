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

## Todo list

- Unit tests listdir.c
- Unit tests printUtils.c
- Unit tests tree.c
- Unit tests listdir.c
- 
 
## Valgrind use

` valgrind --leak-check=full --track-origins=yes ./binTest`