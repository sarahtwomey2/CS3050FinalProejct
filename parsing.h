#ifndef parsing_h
#define parsing_h

#include <stdio.h>
#include <stdlib.h>
#include "input_error.h"

typedef struct fileContent {
    char** memory;
    int* lineSize;
    int* rowSize;
    int** start;
    int** end;
} fileData;

fileData readFile(int argc, char* argv);
void printDoubleChar(fileData);
void freeParsing(fileData);

#endif

