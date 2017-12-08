//
//  main.c
//  RecursiveMaze2
//
//  Created by Sarah Twomey, Jordan Wieberg, Travis Agne & Paul Gillis on 11/30/17.
//  Copyright © 2017 Sarah Twomey. All rights reserved.
//

#include <stdio.h>
#include "parsing.h"

int robotPathFinder(int robot, fileData content);
int recursiveSolve(int x, int y, int robot, fileData content);
void setupRecursiveSolve(fileData content);
void freeRecursiveSolve(fileData content);
void makeWall(int x, int y, fileData content);
int inBounds(int x, int y, fileData content);
void checkOverlap(int x, int y, char move, fileData content);

int** wasHere;
int** paths;

int main(int argc, char * argv[]) {
    fileData content = readFile(argc, *(argv+1));
    /*
     * Robot 1 Path
     */
    int a = robotPathFinder(1, content);
    /*
     * Robot 2 Path
     */
    int b = robotPathFinder(2, content);
    /*
     * Solved maze paths
     */
    if(a == 1 && b == 1) {
        printf("\n\nSolved Maze (+ = robot 1, * = robot 2, ^ = robot path overlap)\n");
        printDoubleChar(content, 0);
        printf("\nSuccessfully found path for robot 1 and 2\n");
    } else {
        printf("\nCould not find way out of maze\n");
    }
    /*
     * Free fileData
     */
    freeParsing(content);
    return 0;
}

int robotPathFinder(int robot, fileData content) {
    setupRecursiveSolve(content);
    if (robot == 1) {
        printf("\nFirst Robot's path (+)\n");
        makeWall(content.start[1][0], content.start[1][1], content);
    } else {
        printf("\nSecond Robot's path (*) Overlaping paths = (^)\n");
        makeWall(content.end[0][0], content.end[0][1], content);
    }
    int a = recursiveSolve(content.start[robot-1][0], content.start[robot-1][1], robot, content);
    if (a == 1) {
        printDoubleChar(content, robot);
    } else {
        printDoubleChar(content, robot);
        printf("\nFailed to find path for robot %d!\n", robot);
    }
    freeRecursiveSolve(content);
    return a;
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
    if (content.memory[y][x] == '#' || wasHere[y][x] || content.memory[y][x] == '-' || paths[y][x] == 1) {
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
    paths = malloc(sizeof(int*)*rowSize);
    int row, col;
    for(row=0; row< rowSize; row++) {
        int colSize = content.lineSize[row];
        wasHere[row] = malloc(sizeof(int)*colSize);
        paths[row] = malloc(sizeof(int)*colSize);
        for(col=0; col < colSize; col++) {
            wasHere[row][col] = 0;
            paths[row][col] = 0;
        }
    }
}

void freeRecursiveSolve(fileData content) {
    int row;
    for(row=0; row < *content.rowSize; row++) {
        free(wasHere[row]);
        free(paths[row]);
    }
    free(wasHere);
    free(paths);
}

void makeWall(int x, int y, fileData content) {
    if (!inBounds(x, y, content)){
        return;
    }
    if(inBounds(x-1, y, content) && content.memory[y][x-1] != '#') {
        paths[y][x-1] = 1;
    }
    if(inBounds(x, y-1, content) && content.memory[y-1][x] != '#') {
        paths[y-1][x] = 1;
    }
    if(inBounds(x+1, y, content) && content.memory[y][x+1] != '#') {
        paths[y][x+1] = 1;
    }
    if(inBounds(x, y+1, content) && content.memory[y+1][x] != '#') {
        paths[y+1][x] = 1;
    }
    if(inBounds(x+1, y+1, content) && content.memory[y+1][x+1] != '#') {
        paths[y+1][x+1] = 1;
    }
    if(inBounds(x-1, y-1, content) && content.memory[y-1][x-1] != '#') {
        paths[y-1][x-1] = 1;
    }
    if(inBounds(x+1, y-1, content) && content.memory[y-1][x+1] != '#') {
        paths[y-1][x+1] = 1;
    }
    if(inBounds(x-1, y+1, content) && content.memory[y+1][x-1] != '#') {
        paths[y+1][x-1] = 1;
    }
}

int inBounds(int x, int y, fileData content) {
    if (0 > y || y >= *content.rowSize) {
        return 0;
    }
    if (-1 < x && x < content.lineSize[y]) {
        return 1;
    }
    return 0;
}

void checkOverlap(int x, int y, char move, fileData content) {
    char opp = '+';
    if (move == '+') {
        opp = '*';
    }
    if (content.memory[y][x] == opp) {
        content.memory[y][x] = '^';
    } else if(content.memory[y][x] != 'S' && content.memory[y][x] != 'F') {
        content.memory[y][x] = move;
    }
}
