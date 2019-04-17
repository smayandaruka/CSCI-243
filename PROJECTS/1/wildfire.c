// Smayan Daruka
// sd9080
// Project 1 - Wildfire

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "display.h"

#define DEFAULT_BURN 10             // Proportion of trees initially burning
#define DEFAULT_PROB_CATCH 30       // Probability of a tree to catch fire
#define DEFAULT_DENSITY 50          // Density of the forest
#define DEFAULT_PROB_NEIGHBOR 25    // Proportion of neighbors on fire to trigger DEFAULT_PROB_CATCH
#define DEFAULT_PRINT_COUNT 0       // Number of cycles to print before quitting
#define DEFAULT_SIZE 10             // Default size of the forest

#define EMPTY '0'   // Empty
#define TREE '1'    // non-inflamed tree
#define FIRE1 '2'   // Burning tree in first cycle
#define FIRE2 '3'   // Burning tree in second cycle
#define BURNED '5'  // Burned tree

static int D_B = DEFAULT_BURN;              // Proportion of trees initially burning
static int D_P_Catch = DEFAULT_PROB_CATCH;  // Probability of a tree to catch fire
static int D_D = DEFAULT_DENSITY;           // Density of the forest
static int D_P_N = DEFAULT_PROB_NEIGHBOR;   // Proportion of neighbors on fire to trigger DEFAULT_PROB_CATCH
static int D_P_Count = DEFAULT_PRINT_COUNT; // Number of cycles to print before quitting
static int D_S = DEFAULT_SIZE;              // Default size of the forest

static int curCycle = 0;            // stores the current cycle which is printed below each forest
static int curChanges = 0;          // stores the number of changes made in a cycle
static int cumulativeChanges = 0;   // stores the total number of changes made throughout the running of the program


/*
printVariables function prints all the settings of the forest like density, prob_burn, etc and the cycle information
*/
void printVariables(){
    printf("size %i, pCatch %.2f, density %.2f, pBurning %.2f, pNeighbor %.2f\n", D_S, ((float)D_P_Catch/100), ((float)D_D/100), ((float)D_B/100), ((float)D_P_N/100));
    printf("cycle %d, changes %d, cumulative changes %d.\n",curCycle,curChanges,cumulativeChanges);
}

/*
usage function is printed when the user invokes the program using the -H argument or when an invalid argument is entered
*/
void usage(){
    fprintf(stderr, "usage: wildfire [options]\n");
    fprintf(stderr, "By default, the simulation runs in overlay display mode.\n");
    fprintf(stderr, "The -pN option makes the simulation run in print mode for up to N cycles.\n");
    fprintf(stderr, "\nSimulation Configuration Options:\n");
    fprintf(stderr, "  -H   # View simulation options and quit.\n");
    fprintf(stderr, "  -bN  # proportion of trees that are already burning. 0 < N < 101.\n");
    fprintf(stderr, "  -cN  # probability that a tree will catch fire. 0 < N < 101.\n");
    fprintf(stderr, "  -dN  # density/proportion of trees in the grid. 0 < N < 101.\n");
    fprintf(stderr, "  -nN  # proportion of neighbors that influence a tree catching fire. -1 < N < 101.\n");
    fprintf(stderr, "  -pN  # number of cycles to print before quitting. -1 < N < ...\n");
    fprintf(stderr, "  -sN  # simulation grid size. 4 < N < 41.\n");
}

/*
initialize_forest function initializes the forest with empty spots, live trees, and burning trees.
It takes in the 2-D character array of the forest.
*/
void initialize_forest(char forest[][D_S]){
    int row, col;
    int totalSpots = D_S * D_S; // total number of spots in the forest.
    int numTrees = (totalSpots * D_D) / 100; // calculates the number of trees in the forest using DEFAULT_DENSITY
    int burningTrees = (numTrees * D_B) / 100; // calculates the number of burning trees in the forest using DEFAULT_BURN

    //Initializes the forest
    for(row = 0; row < D_S; row++){
        for(int col = 0;col < D_S;col++){
            forest[row][col] = EMPTY;
        }
    }

    // Initializes all (non-inflamed and burning) trees in the forest
    while(numTrees > 0){
        row = rand() % (D_S);
        col = rand() % (D_S);
        if(forest[row][col] != TREE){
            forest[row][col] = TREE;
            numTrees--;
        }
    }

    // sets non-inflamed trees to burning tree in first cycle
    while(burningTrees > 0){
        row = rand() % (D_S);
        col = rand() % (D_S);
        if(forest[row][col] == TREE){
            forest[row][col] = FIRE1;
            burningTrees--;
        }
    }
}

/*
iterate_forest function is used to cycle/iterate through the forest.
This function keeps count of current changes and cumulative changes made in the forest.
It takes in the 2-D character array of the forest.
*/
int iterate_forest(char forest[][D_S]){
    char forest_copy[D_S][D_S]; // stores a replica of the initial forest.
    int row, col;
    float propBurning = 0; // Proportion of neighbors burning
    int catchChance = 0; // random number that will be used to check if a tree will catch fire
    float propNeighbors = (float) (D_P_N / 100); // a decimal value of the proportion of neighbors on fire to trigger DEFAULT_PROB_CATCH
    int trees = 0; // stores the neighboring non-inflamed trees
    int fires = 0; // stores the neighboring trees that are on fire
    curChanges = 0; // keeps count of changes made in the forest in a cycle
    int burningTree = 0;

    // creates a copy of the forest
    for(row = 0; row < D_S; row++){
        for(col = 0; col < D_S; col++){
            forest_copy[row][col] = forest[row][col];
        }
    }

    for(row = 0; row < D_S; row++){
        for(col = 0; col < D_S; col++){
            // This checks if the value in the current spot is between 1 and 5 exclusively.
            // This implies that a tree is on fire.
            // First iteration: value changes from 2 to 3 indicating the first burn cycle of the tree
            // Second iteration: value changes from 3 to 4 indicating the second burn cycle of the tree
            // Third iteration: the tree burns out changing the value to 5
            if(forest[row][col] > TREE && forest[row][col] < BURNED){
                forest[row][col]++;
                // This variable keeps track if a tree changed burning state but no visually apparent changes were made to the forest
                // for ex: a tree changing burn state from cycle 1 to cycle 2 is not a change which caused the program to quit before all fires burned out.
                burningTree++;
                // Checks if the tree is burned as 1 change is considered going from a non-inflamed tree to a burning tree or from burning tree to burned tree.
                if(forest[row][col] == BURNED){
                    curChanges++;
                    cumulativeChanges++;
                }
            }
            // If there is a non-inflamed tree in the current spot
            else if(forest[row][col] == TREE){
                // Calculating values for North West
                if(row > 0 && col > 0){
                    if(forest_copy[row - 1][col - 1] == TREE)
                        trees++;
                    if(forest_copy[row - 1][col - 1] > TREE && forest_copy[row - 1][col - 1] < BURNED)
                        fires++;
                }

                // Calculating values for North
                if(row > 0){
                    if(forest_copy[row - 1][col] == TREE)
                        trees++;
                    if(forest_copy[row - 1][col] > TREE && forest_copy[row - 1][col] < BURNED)
                        fires++;
                }

                // Calculating values for North East
                if(row > 0 && col < (D_S - 1)){
                    if(forest_copy[row - 1][col + 1] == TREE)
                        trees++;
                    if(forest_copy[row - 1][col + 1] > TREE && forest_copy[row - 1][col + 1] < BURNED)
                        fires++;
                }

                // Calculating values for West
                if(col > 0){
                    if(forest_copy[row][col - 1] == TREE)
                        trees++;
                    if(forest_copy[row][col - 1] > TREE && forest_copy[row][col - 1] < BURNED)
                        fires++;
                }

                // Calculating values for East
                if(col < (D_S - 1)){
                    if(forest_copy[row][col + 1] == TREE)
                        trees++;
                    if(forest_copy[row][col + 1] > TREE && forest_copy[row][col + 1] < BURNED)
                        fires++;
                }

                // Calculating values for South West
                if(row < (D_S - 1) && col > 0){
                    if(forest_copy[row + 1][col - 1] == TREE)
                        trees++;
                    if(forest_copy[row + 1][col - 1] > TREE && forest_copy[row + 1][col - 1] < BURNED)
                        fires++;
                }

                // Calculating values for South
                if(row < (D_S - 1)){
                    if(forest_copy[row + 1][col] == TREE)
                        trees++;
                    if(forest_copy[row + 1][col] > TREE && forest_copy[row + 1][col] < BURNED)
                        fires++;
                }

                // Calculating values for South East
                if(row < (D_S - 1) && col < (D_S - 1)){
                    if(forest_copy[row + 1][col + 1] == TREE)
                        trees++;
                    if(forest_copy[row + 1][col + 1] > TREE && forest_copy[row + 1][col + 1] < BURNED)
                        fires++;
                }

                // Checks if the fires are greater than 0 so as to calculate the proportion of neighbors burning
                if(fires > 0)
                    propBurning = ((float) fires) / (trees + fires);

                //Random number between 1 and 100 that is used to check if the tree will catch fire
                catchChance = rand() % 100;
                if((propBurning > propNeighbors) && (catchChance < D_P_Catch)){
                    forest[row][col]++; // The tree catches fire
                    curChanges++; // increments the counter as a change was made in the previous line
                    cumulativeChanges++;
                }
            }
        }
    }
    // checks if any changes were made in this cycle.
    // 0 changes implies there are no more fires and the program can quit
    if(burningTree == 0 && curChanges == 0)
        return 1;
    else
        return 0;
}

/*
printForestCycles function prints the forest to the console. This implies that the -pN option was specified.
It takes in the 2-D character array of the forest.
*/
void printForestCycles(char forest[][D_S]){
    for(int row = 0; row < D_S; row++){
        for(int col = 0; col < D_S; col++){
            // printing empty spots in the forest
            if(forest[row][col] == EMPTY){
                printf("%c", ' ');
            }
            // printing non-inflamed trees in the forest
            else if(forest[row][col] == TREE){
                printf("%c", 'Y');
            }
            // printing burned trees in the forest
            else if(forest[row][col] == BURNED){
                printf("%c", '.');
            }
            // printing burning trees in the forest
            else if(forest[row][col] > TREE && forest[row][col] < BURNED){
                printf("%c", '*');
            }
        }
        printf("\n");
    }
}

/*
printForestOverlay function prints the forest in overlay mode meaning on top of the previous forest
It takes in the 2-D character array of the forest.
*/
void printForestOverlay(char forest[][D_S]){
    int row, col;
    set_cur_pos(1,0);
    for(row = 0; row < D_S; row++){
        for(col = 0; col < D_S; col++){
            if(forest[row][col] == EMPTY)
                put(' ');
            else if(forest[row][col] == TREE)
                put('Y');
            else if(forest[row][col] > TREE && forest[row][col] < BURNED)
                put('*');
            else if(forest[row][col] == BURNED)
                put('.');
            else
                put(forest[row][col]);
        }
        printf("\n");
    }
}

int main(int argc, char * argv[]){
    srand(41); //seed the random number generator to 41 as mentioned in the write-up
    int opt;
    int changes = 0; // variable used later for checking if any changes were made in a cycle

    while((opt = getopt(argc, argv, "Hb:c:d:n:p:s:")) != -1){
        switch( opt ){
            case 'H':
                usage();
                return 0;
                break;

            case 'b':
                D_B = (int)strtol(optarg, NULL, 10);
                if(D_B > 0 && D_B < 101){
                    break;
                }
                else{
                    fprintf(stderr, "(-bN) proportion already burning. must be an integer in [1...100].\n");
                    usage();
                    return EXIT_FAILURE;
                }

            case 'c':
                D_P_Catch = (int)strtol(optarg, NULL, 10);
                if(D_P_Catch > 0 && D_P_Catch < 101){
                    break;
                }
                else{
                    fprintf(stderr, "(-cN) probability a tree will catch fire. must be an integer in [1...100].\n");
                    usage();
                    return EXIT_FAILURE;
                }

            case 'd':
                D_D= (int)strtol(optarg, NULL, 10);
                if(D_D > 0 && D_D < 101){
                    break;
                }
                else{
                    fprintf(stderr, "(-dN) density of trees in the grid must be an integer in [1...100].\n");
                    usage();
                    return EXIT_FAILURE;
                }

            case 'n':
                D_P_N= (int)strtol(optarg, NULL, 10);
                if(D_P_N > -1 && D_P_N < 101){
                    break;
                }
                else{
                    fprintf(stderr, "(-nN) neighbors influence catching fire must be an integer in [0...100].\n");
                    usage();
                    return EXIT_FAILURE;
                }

            case 'p':
                D_P_Count= (int)strtol(optarg, NULL, 10);
                if(D_P_Count > -1 && D_P_Count < 10000){
                    break;
                }
                else{
                    fprintf(stderr, "(-pN) number of cycles to print. must be an integer in [0...10000].\n");
                    usage();
                    return EXIT_FAILURE;
                }

            case 's':
                D_S = (int)strtol(optarg, NULL, 10);
                if(D_S > 4 && D_S < 41){
                    break;
                }
                else{
                    fprintf(stderr, "(-sN) simulation grid size must be an integer in [5...40].\n");
                    usage();
                    return EXIT_FAILURE;
                }
        }
    }

    char forest[D_S][D_S]; // create the forest
    initialize_forest(forest); // initialize the forest

    // Checks if the -pN argument was specified. If it was, then it prints in print mode for the specified number of cycles
    if(D_P_Count > 0){
        printForestCycles(forest); // this prints the initial state of the forest
        printVariables(); // This prints all the variables
        for(int count = 0; count < D_P_Count; count++){
            changes = iterate_forest(forest); // assigns the value returned from the advance function to determine if any changes were made
            curCycle++; // increments the current cycle counter
            printForestCycles(forest);
            printVariables();

            // checks if the value is one implying there were no changes made and all fires are out. Quits the program
            if(changes == 1){
                printf("Fires are out\n");
                break;
            }
        }
        return 0;
    }
    // else we print the forest in overlay mode
    else{
        clear();
        printForestOverlay(forest); // this prints the initial state of the forest
        printVariables(); // This prints all the variables

        //checks whether any changes were made based on the return value of the advance function
        while(changes != 1){
            usleep(750000);
            changes = iterate_forest(forest);
            curCycle++; // increments the current cycle counter
            printForestOverlay(forest);
            printVariables();
        }
        printf("Fires are out.\n");
        return 0;
    }
}
