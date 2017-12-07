//
//  main.c
//  RecursiveMaze2
//
//  Created by Sarah Twomey on 11/30/17.
//  Copyright © 2017 Sarah Twomey. All rights reserved.
//

#include <stdio.h>
#include "parsing.h"

//void solveMaze(int x, int y);
int recursiveSolve(int x, int y, char** maze, fileData content);



int wasHere[200][500];
int correctPath[200][500];
//int width = 6;
//int height = 6;

int main(int argc, char * argv[]) {
    
    fileData content = readFile(argc, *(argv+1));
    //char maze[content.rowSize[0]][content.lineSize[0]] = content.memory;
    
    for(int row=0; row< *content.rowSize; row++) {
        for(int col=0; col < content.lineSize[row]; col++) {
            wasHere[row][col] = 0;
            correctPath[row][col] = 0;
        }
    }
    printf("\ntest");
    int b = recursiveSolve(content.start[0][0], content.start[0][1], content.memory, content);
    
    printf("x = %d, y = %d", content.start[0][0], content.start[0][1]);
    
    
    if(b == 1) {
        printf("\nSuccess");
    } else {
        printf("\nCould not find way out of maze");
    }
    
    char printmaze[100][200];
    
    printf("\n\nprinting new maze:\n");
    printDoubleChar(content);
    
    // Will leave you with a boolean array (correctPath)
    // with the path indicated by true values.
    // If b is false, there is no solution to the maze
    return 0;
}



int recursiveSolve(int y, int x, char** maze, fileData content) {
    //0 = false, 1 = true
    //printf("recursiveSolve");
    printf("\nsymbol: %c", maze[x][y]);
    
    if (maze[x][y] == 'E') return 1; // If you reached the end
    if (maze[x][y] == '#' || wasHere[x][y]) {
        //printf("\n%c\n", maze[x][y]);
        return 0;
    }
    // If you are on a wall or already were here
    wasHere[x][y] = 1;
    if (x != 0) // Checks if not on left edge
        if (recursiveSolve(x-1, y, maze, content)) { // Recalls method one to the left
            correctPath[x][y] = 1; // Sets that path value to true;
            maze[x][y] = '+'; //changing value from . to +
            return 1;
        }
    if (x != content.lineSize[y] - 1) // Checks if not on right edge
        if (recursiveSolve(x+1, y, maze, content)) { // Recalls method one to the right
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    if (y != 0)  // Checks if not on top edge
        if (recursiveSolve(x, y-1, maze, content)) { // Recalls method one up
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    if (y != content.rowSize[0] - 1) // Checks if not on bottom edge
        if (recursiveSolve(x, y+1, maze, content)) {  //Recalls method one down
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    
    maze[x][y] = 'x';
    return 0;
}

