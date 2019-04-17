/// 
/// File: triangle.c 
/// 
/// A program to print out multiple "pyramid" triangles of the form:
/// <pre>
///   *
///  ***
/// *****
/// </pre>
/// 
/// @author sd9080 : Smayan Daruka
/// 
// // // // // // // // // // // // // // // // // // // // // // // // 

// TODO_ADD_#INCLUDES_ HERE
#include <stdio.h>

/**
 *  Function: drawTriangle
 *
 *  Description: Draw a 'pyramid' triangle whose base width is 'size'.
 *  Note: If size is even, the function makes a 'size + 1' pyramid triangle. 
 * 
 *  @param size  the width of the base of the triangle to draw
 */
// TODO_WRITE_DRAWTRIANGLE_FUNCTION HERE
void drawTriangle(int size){
    int stars = 0;
    int spaces = 0;

    if ((size % 2) ==  0)
	size++;
    if (size != 0)
	stars = 1;
    spaces = (size-1)/2;

    for (int count = 0; count < (size+1)/2; count++){
	for (int x = 0; x < spaces; x++){
	    printf(" ");
	}
	for(int star = 0; star < stars; star++){
	    printf("*");
	}

	printf("\n");
	spaces-=1;
	stars+=2;
    }
    printf("\n");
}

/**
 *  Function: main 
 *
 *  Description: draws pyramid triangles of size 1, 5, and '6'.
 *
 *  @returns errorCode  error Code; EXIT_SUCCESS if no error
 */
// TODO_WRITE_MAIN_FUNCTION HERE
int main(void){
    printf("\n");
    drawTriangle(1);
    drawTriangle(5);
    drawTriangle(6);

    return 0;
}
