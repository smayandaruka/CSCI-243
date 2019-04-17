/*
 * File:    $Id: display.c,v 1.3 2014/11/22 16:45:32 csci243 Exp $
 *
 * Revision History: 
 *    $Log: display.c,v $
 *    Revision 1.3  2014/11/22 16:45:32  csci243
 *    Removed BAD pause function.
 *
 *    Revision 1.2  2014/11/22 15:13:41  csci243
 *    Changed file names to lower case.
 *
 *    Revision 1.1  2014/11/19 15:09:16  jeh
 *    Initial revision
 *
 */

#include <stdio.h>

#include "display.h"

//
// Name:    clear
//
void clear() {
    printf( "\033[2J" );
    fflush( stdout );
} // clear

//
// Name:    put
//
void put( char character ) {
    putchar( character );
    fflush( stdout );
} // clear

//
// Name:    set_cur_postition
//
void set_cur_pos( int rCursor, int cCursor) {
    printf( "\033[%d;%dH", rCursor, cCursor );
} // set_cur_pos

