// username: sd9080
// name: Smayan Daruka
// email: sd9080@rit.edu
// This program parses a CSV in order to provide a summary of the statistics for the dataset.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int lines = 1024; // refers to the maximum number of lines that can be read
    char string[256]; // a char array to store the data read
    int line; // used in the for loop for iteration
    double meanPopulation = 0; // variable to store the mean population that will be calculated at the end

    //variables for parsing data into their respective variables as they are read
    char zipcode[256];
    char population[256];
    char medianage[256];
    char totalmales[256];
    char totalfemales[256];
    char totalhouseholds[256];
    char averagehousehold[256];

    // variable used to store the converted current population from a string to a double
    double bufPopulation = 0;

    // variables to keep track of number of zipcodes and total population
    static int numofzipcodes = 0;
    static double totalPopulation = 0;

    for(line = 0; line < lines && fgets(string, 256, stdin); line++){
        // the following code parses the data that has been read into the variable string
        strcpy(zipcode, strtok(string , ","));
        strcpy(population, strtok(NULL , ","));
        strcpy(medianage, strtok(NULL , ","));
        strcpy(totalmales, strtok(NULL , ","));
        strcpy(totalfemales, strtok(NULL , ","));
        strcpy(totalhouseholds, strtok(NULL , ","));
        strcpy(averagehousehold, strtok(NULL , ","));

        // counter starts at 1 because the first line is a header which is to be ignored
        if(line > 0){
            bufPopulation = strtod (population, NULL); // converts the population
            totalPopulation += bufPopulation;
            numofzipcodes++;
        }
    }
    meanPopulation = totalPopulation / numofzipcodes; // calculated the mean population

    printf("ZipCodes=%d\n", numofzipcodes);
    printf("Population=%.0f\n", totalPopulation);
    printf("MeanPopByZip=%.1f\n", meanPopulation);

    return 0;
}

