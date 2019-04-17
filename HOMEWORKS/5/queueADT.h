// File: $Id: queueADT.h,v 1.4 2017/04/19 12:51:39 csci243 Exp $
//
// Description:  Interface to the Queue ADT module
//
// Author:  wrc

#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

#include <stdbool.h>

//
// Only define the QueueADT type if we are _not_ compiling the
// module's implementation file.
//
// In the implementation file, define the QueueADT type as you need
// to for the implementation, and then define the symbol _QUEUE_IMPL_
// immediately before including this header file to prevent a
// redefinition of the type.
//

#ifndef _QUEUE_IMPL_
/// QueueADT is a pointer to an abstract queue data structure whose
/// payload data type is 'generic', implemented as void * in this interface.

typedef struct { } * QueueADT;
#endif

/// Create a QueueADT which uses the supplied function as a comparison
/// routine.
///
/// The comparison function takes two void * parameters, and returns
/// an integer result which indicates the relationship between the
/// two things:
///
///	Result	Relationship
///	======	===========
///	 < 0	a < b
///	 = 0	a == b
///	 > 0	a > b
///
/// where ">" and "<" are dependent upon the data being compared
///
/// @param cmp the address of the comparison function to be used for
///    ordering this queue, or NULL if standard FIFO behavior is desired
/// @return a QueueADT instance, or NULL if the allocation fails
QueueADT que_create( int (*cmp)(const void * a, const void * b) );

/// Tear down and deallocate the supplied QueuADT.
///
/// @param queue - the QueueADT to be manipulated
void que_destroy( QueueADT queue );

/// Remove all contents from the supplied QueueADT.
///
/// @param queue - the QueueADT to be manipuated
void que_clear( QueueADT queue );

/// Insert the specified data into the Queue in the appropriate place
///
/// Uses the queue's comparison function to determine the appropriate
/// place for the insertion.
///
/// @param queue the QueueADT into which the value is to be inserted
/// @param data the data to be inserted
/// @exception If the value cannot be inserted into the queue for
///     whatever reason (usually implementation-dependent), the program
///     should terminate with an error message.  This can be done by
///     printing an appropriate message to the standard error output and
///     then exiting with EXIT_FAILURE, or by having an assert() fail.
void que_insert( QueueADT queue, void * data );

/// Remove and return the first element from the QueueADT.
///
/// @param queue the QueueADT to be manipulated
/// @return the value that was removed from the queue
/// @exception If the queue is empty, the program should terminate
///     with an error message.  This can be done by printing an
///     appropriate message to the standard error output and then
///     exiting with EXIT_FAILURE, or by having an assert() fail.
void * que_remove( QueueADT queue );

/// Indicate whether or not the supplied Queue is empty
///
/// @param the QueueADT to be tested
/// @return true if the queue is empty, otherwise false
bool que_empty( QueueADT queue );

#endif

