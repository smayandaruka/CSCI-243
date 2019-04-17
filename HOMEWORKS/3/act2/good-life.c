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

#include <stdio.h>
#include <stdlib.h>

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

            printf("%c", life[row][col]);
        }
        printf("\n");
    }
}

int main(void){
    int size = 20;
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

    while ( count < 100 ) {
        allRules(size, life);
        printf("\ngeneration: %d\n", count);
        count++;
    }

    return 0;
}
