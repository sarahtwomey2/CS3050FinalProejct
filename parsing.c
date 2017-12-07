#include "parsing.h"

fileData readFile(int argc, char* argv) {
    if (argc != 2) {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    fileData content;
    
    // Open the input file
    FILE* input = fopen(argv, "r");
    if (!input) {
        exit(INPUT_FILE_FAILED_TO_OPEN);
    }
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
    
    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c != ' ' && c != '#' && c != 'S' && c != 'E' && c != 'F' && c != 'L' && c != EOF && c != '\n') {
            //TODO change that to invalid character
            exit(PARSING_ERROR_INVALID_FORMAT);
        }
        if (c == '\n') {
            content.rowSize[0] += 1;
            content.memory = realloc(content.memory, (content.rowSize[0]+1) * sizeof(char*));
            content.memory[content.rowSize[0]] = malloc(sizeof(char));
            content.lineSize = realloc(content.lineSize, (content.rowSize[0]+1)*sizeof(int));
            content.lineSize[content.rowSize[0]] = 0;
        } else {
            if (c == 'S') {
                content.start[0][0] = content.lineSize[content.rowSize[0]];
                content.start[0][1] = content.rowSize[0];
            } else if (c == 'F') {
                content.start[1][0] = content.lineSize[content.rowSize[0]];
                content.start[1][1] = content.rowSize[0];
            } else if (c == 'E') {
                content.end[0][0] = content.lineSize[content.rowSize[0]];
                content.end[0][1] = content.rowSize[0];
            } else if (c == 'L') {
                content.end[0][0] = content.lineSize[content.rowSize[0]];
                content.end[0][1] = content.rowSize[0];
            }
            content.memory[content.rowSize[0]] = realloc(content.memory[content.rowSize[0]], (content.lineSize[content.rowSize[0]]+1)*sizeof(char));
            content.memory[content.rowSize[0]][content.lineSize[content.rowSize[0]]] = c;
            content.lineSize[content.rowSize[0]] += 1;
        }
    }
    
    if (*content.rowSize == 0 && *content.lineSize == 0 && c == EOF) {
        exit(PARSING_ERROR_EMPTY_INPUT_FILE);
    }
    
    //close the input file
    if (fclose(input) == EOF) {
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
    printDoubleChar(content);
    return content;
}

void printDoubleChar(fileData content) {
    int i, j;
    for (i = 0; i < content.rowSize[0]; i++) {
        for (j = 0; j < content.lineSize[i]; j++) {
            printf("%c", content.memory[i][j]);
        }
        printf("\n");
    }
}

void freeParsing(fileData content) {
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

