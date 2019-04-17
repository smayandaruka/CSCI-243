/// file: readcsv.c
/// description: implementation for circle functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int lines = 1024;
    char string[256];
    int line;
    int numberoflines = 0;

    char zipcode[256];
    char population[256];
    char medianage[256];
    char totalmales[256];
    char totalfemales[256];
    char totalhouseholds[256];
    char averagehousehold[256];


//    static int numofzipcodes = 0;
//    static double totalPopulation = 0;
//    double meanPopulation = 0;

    for(line = 0; line < lines && fgets(string, 256, stdin); line++){

        printf("%s", string);
        numberoflines++;

        strcpy(zipcode, strtok(string , ","));
        strcpy(population, strtok(NULL , ","));
        strcpy(medianage, strtok(NULL , ","));
        strcpy(totalmales, strtok(NULL , ","));
        strcpy(totalfemales, strtok(NULL , ","));
        strcpy(totalhouseholds, strtok(NULL , ","));
        strcpy(averagehousehold, strtok(NULL , ","));

    }






    printf("%d\n", line);
    printf("%d\n", numberoflines);

    return 0;
}

void print(){

        printf("%s\n", zipcode);
        printf("%s\n", population);
        printf("%s\n", medianage);
        printf("%s\n", totalmales);
        printf("%s\n", totalfemales);
        printf("%s\n", totalhouseholds);
        printf("%s\n", averagehousehold);

}
