#include "parsing.h"
#include <stdbool.h>

fileData readFile(int argc, char* argv) {
    //Check if correct number of commands line args. Make sure input file has a path
    if (argc != 2) {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    fileData content;
    
    // Open the input file and check if the file can be opened
    FILE* input = fopen(argv, "r");
    if (!input) {
        exit(INPUT_FILE_FAILED_TO_OPEN);
    }
    
    //Allocates memory for fileData
    content.memory = malloc(sizeof(char*));
    content.lineSize = malloc(sizeof(int));
    content.rowSize = malloc(sizeof(int));
    content.start = malloc(2*sizeof(int*));
    content.start[0] = malloc(2*sizeof(int));
    content.start[1] = malloc(2*sizeof(int));
    content.end = malloc(2*sizeof(int));
    content.end[0] = malloc(2*sizeof(int));
    content.end[1] = malloc(2*sizeof(int));
    content.memory[0] = malloc(sizeof(char));
    content.lineSize[0] = 0;
    
    //Reads in input file character by character
    char c;
    bool isS = false;
    bool isF = false;
    bool isE = false;
    bool isL = false;
    
    while ((c = fgetc(input)) != EOF) {
        if (c != ' ' && c != '#' && c != 'S' && c != 'E' && c != 'F' && c != 'L' && c != EOF && c != '\n') {
            //Check if invalid character inside input file
            exit(PARSING_ERROR_INVALID_FORMAT);
        }
        if (c == '\n') {
            //Adjusts memory for more lines
            content.rowSize[0] += 1;
            content.memory = realloc(content.memory, (content.rowSize[0]+1) * sizeof(char*));
            content.memory[content.rowSize[0]] = malloc(sizeof(char));
            content.lineSize = realloc(content.lineSize, (content.rowSize[0]+1)*sizeof(int));
            content.lineSize[content.rowSize[0]] = 0;
        } else {
            //Adjusts memory for more characters
            if (c == 'S') {
                content.start[0][0] = content.lineSize[content.rowSize[0]];
                content.start[0][1] = content.rowSize[0];
                isS = true;
            } else if (c == 'F') {
                content.start[1][0] = content.lineSize[content.rowSize[0]];
                content.start[1][1] = content.rowSize[0];
                isF = true;
            } else if (c == 'E') {
                content.end[0][0] = content.lineSize[content.rowSize[0]];
                content.end[0][1] = content.rowSize[0];
                isE = true;
            } else if (c == 'L') {
                content.end[1][0] = content.lineSize[content.rowSize[0]];
                content.end[1][1] = content.rowSize[0];
                isL = true;
            }
            content.memory[content.rowSize[0]] = realloc(content.memory[content.rowSize[0]], (content.lineSize[content.rowSize[0]]+1)*sizeof(char));
            content.memory[content.rowSize[0]][content.lineSize[content.rowSize[0]]] = c;
            content.lineSize[content.rowSize[0]] += 1;
        }
    }
    
    //Check if input file is empty
    if (*content.rowSize == 0 && *content.lineSize == 0 && c == EOF) {
        exit(PARSING_ERROR_EMPTY_INPUT_FILE);
    }
    
    //close the input file and check if the input file could be closed
    if (fclose(input) == EOF) {
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
    printf("Maze read in from input file\n");
    printDoubleChar(content, 0);
    
    if(isS == false) {
        printf("Error: S is not in maze.");
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    if(isF == false) {
        printf("Error: F is not in maze.");
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    if(isE == false) {
        printf("Error: E is not in maze.");
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    if(isL == false) {
        printf("Error: L is not in maze.");
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    
    return content;
}

void printDoubleChar(fileData content, int robot) {
    //Prints double char pointer in fileData(memory)
    int i, j;
    for (i = 0; i < content.rowSize[0]; i++) {
        for (j = 0; j < content.lineSize[i]; j++) {
            if ((robot == 1 && content.memory[i][j] == '*') || (robot == 2 && content.memory[i][j] == '+')) {
                printf("%c", ' ');
            } else if(content.memory[i][j] == '^' && robot > 0) {
                char temp[2] = {'+','*'};
                printf("%c", temp[robot-1]);
            } else {
                printf("%c", content.memory[i][j]);
            }
        }
        printf("\n");
    }
}

void freeParsing(fileData content) {
    //Frees memory for fileData
    int i;
    for (i = 0; i <= content.rowSize[0]; i++) {
        free(content.memory[i]);
    }
    free(content.start[0]);
    free(content.start[1]);
    free(content.start);
    free(content.end[0]);
    free(content.end[1]);
    free(content.end);
    free(content.memory);
    free(content.lineSize);
    free(content.rowSize);
}

