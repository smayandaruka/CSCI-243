/*
 * File:    $Id: display.h,v 1.5 2015/08/11 19:17:46 bks Exp $
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
 *    Revision 1.5  2015/08/11 19:17:46  bks
 *    corrected documentation for set_cur_pos --bks
 *
 *    Revision 1.4  2015/08/11 19:12:30  bks
 *    upgraded docs to work with doxygen --bks
 *
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


/// Clear the terminal window of all characters.
/// @post: The terminal window display is modified and cleared.
/// 
void clear();

/// Cause a character to appear at the current position of the cursor.
/// The terminal window display is modified.
///
/// @param character: the character to display
///
void put( char character );

/// Move the cursor to the position specified.
/// No visible display changes, but the cursor position is modified.
/// Coordinate values increase rightward and downward.
/// The coordinate system is such that the leftmost column is numbered 0,
/// and the topmost row is numbered 1. To make the cursor go to
/// the top-left location on the terminal, call set_cur_pos( 1, 0 );
///
/// @param rCursor: the destination row
/// @param cCursor: the destination column
/// 
void set_cur_pos( int rCursor, int cCursor);

#endif
