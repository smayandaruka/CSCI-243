/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; e.g. mix of TAB and spaces indentation
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///

//name: Smayan Daruka
//username: sd9080

#define _BSD_SOURCE
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*function for program header*/
void header(void){
    printf("\n\t..Welcome to the Game of life..\n");
}

// I deleted the 3 rules functions namely survivalRule, birthRule, and deathRule. Created my own combined function.

// This is the combined function and the logic has been corrected as well.
void allRules(int size, char life[][size]){
    int row, col;
    int neighbors = 0;
    for(row = 0; row<size; row++){
        for(col = 0; col<size; col++){
            if(life[row][col] == '*')
                neighbors++;
            if(life[(row - 1) % size][(col - 1) % size] == '*')
                neighbors++;
            if(life[(row - 1) % size][col] == '*')
                neighbors++;
            if(life[(row - 1) % size][(col + 1) % size] == '*')
                neighbors++;
            if(life[row][(col - 1) % size] == '*')
                neighbors++;
            if(life[row][(col + 1) % size] == '*')
                neighbors++;
            if(life[(row + 1) % size][(col - 1) % size] == '*')
                neighbors++;
            if(life[(row + 1) % size][col] == '*')
                neighbors++;
            if(life[(row + 1) % size][(col + 1) % size] == '*')
                neighbors++;

            if (life[row][col] == '*' && neighbors == 2)
                life[row][col] = '*';
            else  if(neighbors == 3)
                life[row][col] = '*';
            else
                life[row][col] = ' ';

            neighbors = 0;

            // used the function supplied in display.c to print the generation
            put(life[row][col]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    int size = 20;
    // for the extra credit.
    // I simply check if argc is greater than 1 which implies a command-line argument
    // Then I set that argument to size which overwrites the default.
    if(argc > 1)
        size = strtol(argv[1], NULL, 10);

    char life[size][size];
    int orgs, i, row, col;
    int count = 0;

    header();

    printf("\nPlease enter the initial number of organisms: ");
    scanf("%i", &orgs);
    srand( 31 );

    for(i = 0; i<orgs; i++){
        row = rand();
        row %= size;
        col = rand();
        col %= size;
        life[row][col] = '*';
    }
    // calls the clear function to clear the screen only once after getting the number of organisms
    clear();

    // infinite loop as mentioned in the write-up
    while ( 1 ) {
        set_cur_pos(1, 0);
        allRules(size, life);
        printf("%d\n", count);
        count++;
        usleep( 81000 );
    }

    return 0;
}
