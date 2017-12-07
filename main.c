//
//  main.c
//  RecursiveMaze2
//
//  Created by Sarah Twomey on 11/30/17.
//  Copyright © 2017 Sarah Twomey. All rights reserved.
//

#include <stdio.h>

void solveMaze();
int recursiveSolve(int x, int y);

char maze[6][6] = {'S',' ',' ','#','#','#',
                   ' ',' ',' ',' ',' ','#',
                   ' ','#','#','#',' ','#',
                   ' ',' ','#','#','E',' ',
                   '#','#','#','#','#','#',
                   '#',' ','#','#','#','#'};

int wasHere[6][6];
int correctPath[6][6];

int width = 6;
int height = 6;

int main(int argc, const char * argv[]) {
    printf("original: \n");
    int startX, startY, endX, endY;
    
    for(int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            printf(" %c", maze[i][j]);
            if(maze[i][j] == 'S') {
                startX = i;
                startY = j;
            }
            if(maze[i][j] == 'G') {
                endX = i;
                endY = j;
            }
        }
        printf("\n");
    }
    
    
    for (int row = 0; row < 6; row++)
        // Sets boolean Arrays to default values
        for (int col = 0; col < 6; col++){
            wasHere[row][col] = 0;
            correctPath[row][col] = 0;
        }
    
    int b = recursiveSolve(startX, startY);
    
    if(b == 1) {
        printf("\nSuccess");
    } else {
        printf("\nCould not find way out of maze");
    }
    
    printf("\n\nprinting new maze:\n");
    for(int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            printf(" %c", maze[i][j]);
        }
        printf("\n");
    }
    
    // Will leave you with a boolean array (correctPath)
    // with the path indicated by true values.
    // If b is false, there is no solution to the maze
    
    return 0;
}



int recursiveSolve(int x, int y) {
    //0 = false, 1 = true
    
    if (maze[x][y] == 'E') return 1; // If you reached the end
    if (maze[x][y] == '#' || wasHere[x][y]) return 0;
    // If you are on a wall or already were here
    wasHere[x][y] = 1;
    if (x != 0) // Checks if not on left edge
        if (recursiveSolve(x-1, y)) { // Recalls method one to the left
            correctPath[x][y] = 1; // Sets that path value to true;
            maze[x][y] = '+'; //changing value from . to +
            return 1;
        }
    if (x != width - 1) // Checks if not on right edge
        if (recursiveSolve(x+1, y)) { // Recalls method one to the right
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    if (y != 0)  // Checks if not on top edge
        if (recursiveSolve(x, y-1)) { // Recalls method one up
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    if (y != height - 1) // Checks if not on bottom edge
        if (recursiveSolve(x, y+1)) { // Recalls method one down
            correctPath[x][y] = 1;
            maze[x][y] = '+';
            return 1;
        }
    maze[x][y] = 'x';
    return 0;
}
