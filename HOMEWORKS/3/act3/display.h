/*
 * File:    $Id: display.h,v 1.3 2014/12/06 03:04:20 csci243 Exp $
 *
 * Author:  Margaret Reek
 * Contributors: idea borrowed from Neill Graham book, and enhanced
 *      by James Heliotis
 *
 * Description:
 *      Manipulate the display and the cursor in the display.
 *      ANSI character sequences are used to achieve this.
 *      A future version may use the curses library.
 *
 * Revisions: 
 *    $Log: display.h,v $
 *    Revision 1.3  2014/12/06 03:04:20  csci243
 *    Fixed comment about coordinate system.
 *
 *    Revision 1.2  2014/11/22 16:00:02  csci243
 *    Improved comments.
 *
 *    Revision 1.1  2014/11/19 15:09:16  jeh
 *    Initial revision
 *
 */

#ifndef RITCSFIGURES_DISPLAY_H
#define RITCSFIGURES_DISPLAY_H


// Clear the terminal window of all characters.
// The terminal window display is modified.
// 
void clear();

// Cause a character to appear at the current position of the cursor.
// The terminal window display is modified.
//
// Arguments
//   character: the character to be shown
//
void put( char character );

// Move the cursor to position specified.
// No visible display changes, but the cursor is modified.
// The coordinate system is such that the leftmost column and topmost
// row are numbered 1. Coordinate values increase rightward and downward.
//
// Arguments
//   rCursor: the destination row
//   cCursor: the destination column
// 
void set_cur_pos( int rCursor, int cCursor);

#endif
