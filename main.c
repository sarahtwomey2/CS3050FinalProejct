//
//  main.c
//  RecursiveMaze2
//
//  Created by Sarah Twomey on 11/30/17.
//  Copyright © 2017 Sarah Twomey. All rights reserved.
//

#include <stdio.h>
#include "parsing.h"

int recursiveSolve(int x, int y, int robot, fileData content);
void setupRecursiveSolve(fileData content);
void freeRecursiveSolve(fileData content);
void makeWall(int x, int y, char** maze);
void checkOverlap(int x, int y, char move, fileData content);

int** wasHere;

int main(int argc, char * argv[]) {
    
    fileData content = readFile(argc, *(argv+1));
    
    setupRecursiveSolve(content);
    makeWall(content.start[1][1], content.start[1][0], content.memory);
    int a = recursiveSolve(content.start[0][0], content.start[0][1], 1, content);
    printDoubleChar(content, 1);
    freeRecursiveSolve(content);
    
    setupRecursiveSolve(content);
    makeWall(content.end[0][0], content.end[0][1], content.memory);
    int b = recursiveSolve(content.start[1][0], content.start[1][1], 2, content);
    printDoubleChar(content, 2);
    freeRecursiveSolve(content);
    
    if(b == 1 && a == 1) {
        printf("\nSuccess");
        
    } else {
        printf("\nCould not find way out of maze");
    }
    
    printf("\n\nprinting new maze:\n");
    printDoubleChar(content, 0);
    freeParsing(content);
    return 0;
}

int recursiveSolve(int x, int y, int robot, fileData content) {
    //0 = false, 1 = true
    //printf("recursiveSolve");
    //printf("\nsymbol: %c position (x,y): (%d,%d)", maze[x][y], x, y);
    char tempEnd[2] = {'E', 'L'};
    char end = tempEnd[robot-1];
    char tempMove[2] = {'+', '*'};
    char move = tempMove[robot-1];
    
    if (content.memory[y][x] == end) { // If you reached the end
        return 1;
    }
    if (content.memory[y][x] == '#' || wasHere[y][x] || content.memory[y][x] == '-') {
        return 0;
    }
    
    // If you are on a wall or already were here
    wasHere[y][x] = 1;
    if (x != 0) // Checks if not on left edge
        if (recursiveSolve(x-1, y, robot, content) == 1) { // Recalls method one to the left
            checkOverlap(x, y, move, content); //changing value from . to +
            return 1;
        }
    if (x != content.lineSize[y] - 1) // Checks if not on right edge
        if (recursiveSolve(x+1, y, robot, content) == 1)  { // Recalls method one to the right
            checkOverlap(x, y, move, content);
            return 1;
        }
    if (y != 0)  // Checks if not on top edge
        if (recursiveSolve(x, y-1, robot, content) == 1) { // Recalls method one up
            checkOverlap(x, y, move, content);
            return 1;
        }
    if (y != content.rowSize[0] - 1) // Checks if not on bottom edge
        if (recursiveSolve(x, y+1, robot, content) ==1) {  //Recalls method one down
            checkOverlap(x, y, move, content);
            return 1;
        }
    return 0;
}

void setupRecursiveSolve(fileData content) {
    int rowSize = *content.rowSize;
    wasHere = malloc(sizeof(int*)*rowSize);
    for(int row=0; row< rowSize; row++) {
        int colSize = content.lineSize[row];
        wasHere[row] = malloc(sizeof(int)*colSize);
        for(int col=0; col < colSize; col++) {
            wasHere[row][col] = 0;
        }
    }
}

void freeRecursiveSolve(fileData content) {
    for(int row=0; row < *content.rowSize; row++) {
        free(wasHere[row]);
    }
    free(wasHere);
}

void makeWall(int x, int y, char** maze) {
    if(maze[x-1][y] != '#')
        maze[x-1][y] = '-';
    if(maze[x][y-1] != '#')
        maze[x][y-1] = '-';
    if(maze[x+1][y] != '#')
        maze[x+1][y] = '-';
    if(maze[x][y+1] != '#')
        maze[x][y+1] = '-';
    if(maze[x+1][y+1] != '#')
        maze[x+1][y+1] = '-';
    if(maze[x-1][y-1] != '#')
        maze[x-1][y-1] = '-';
    if(maze[x+1][y-1] != '#')
        maze[x+1][y-1] = '-';
    if(maze[x-1][y+1] != '#')
        maze[x-1][y+1] = '-';
}

void checkOverlap(int x, int y, char move, fileData content) {
    char opp = '+';
    if (move == '+') {
        opp = '*';
    }
    if (content.memory[y][x] == opp) {
        content.memory[y][x] = '^';
    } else {
        content.memory[y][x] = move;
    }
}
