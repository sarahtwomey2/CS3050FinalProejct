#ifndef parsing_h
#define parsing_h

#include <stdio.h>
#include <stdlib.h>
#include "input_error.h"

//Struct needed for reading in the input file
typedef struct fileContent {
    char** memory;
    int* lineSize;
    int* rowSize;
    int** start;
    int** end;
} fileData;

//Function Prototypes
fileData readFile(int argc, char* argv);
void printDoubleChar(fileData);
void allocateFileData(fileData);
void freeParsing(fileData);

#endif

