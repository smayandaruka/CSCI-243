/// file: main.c
/// description: simple main program uses the circle module.
/// @author RIT CS Dept.

#include <stdio.h>        // printf
#include "circle.h"    // getArea, getCircumference

/// Computes and displays the area and circumference
/// of a circle of a given radius.
void compute(int radius) {
    printf("Area of circle with radius %d: %f\n", 
           radius, getArea(radius));
    printf("Circumference of circle with radius %d: %f\n", 
           radius, getCircumference(radius));
}

/// main program uses the circle module.
int main(void) {
    compute(1);
    compute(5);
    compute(10);

    return 0;
}
