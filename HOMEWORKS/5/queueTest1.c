// $Id: queueTest1.c,v 1.2 2014/10/13 11:21:22 csci243 Exp $
//
// Description:  test driver for the QueueADT module
//
// This test program creates three queues (one an ascending-ordered
// queue, one a descending-ordered queue, and one a FIFO queue),
// inserts a number of integer items into it, and then removes and
// prints them.
//
// Author:  wrc

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "queueADT.h"

//
// Sequence of test values to be inserted and removed
//

long int testData[] = { 42, 17, -12, 9982, 476, 2912, -22, 3291213, 7782 };
int numData = sizeof(testData) / sizeof(long int);

//
// Comparison function for integers sorted in ascending order
//

int cmp_int64_ascend( const void *a, const void *b ) {
	long int na = (long int) a;
	long int nb = (long int) b;

	return( na - nb );
}

//
// Comparison function for integers sorted in descending order
//

int cmp_int64_descend( const void *a, const void *b ) {
	long int na = (long int) a;
	long int nb = (long int) b;

	return( nb - na );
}

//
// Process insertions/removals using a specific queue
//

void process( QueueADT queue ) {
	long int i;

	fputs( "Inserting: ", stdout );
	for( i = 0; i < numData; ++i ) {
		printf( " %ld", testData[i] );
		que_insert( queue, (void *) testData[i] );
	}

	fputs( "\nRemoving:  ", stdout );
	while( !que_empty(queue) ) {
		i = (long int) que_remove( queue );
		printf( " %ld", i );
	}

	putchar( '\n' );
}


int main( void ) {
	QueueADT up, down, fifo;

	up = que_create( cmp_int64_ascend );
	if( up == NULL ) {
		fputs( "Cannot create ascending queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	down = que_create( cmp_int64_descend );
	if( down == NULL ) {
		fputs( "Cannot create descending queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	fifo = que_create( NULL );
	if( fifo == NULL ) {
		fputs( "Cannot create FIFO queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	puts( "Testing the ascending queue" );
	process( up );

	puts( "\nTesting the descending queue" );
	process( down );

	puts( "\nTesting the FIFO queue" );
	process( fifo );

	que_destroy( up );
	que_destroy( down );
	que_destroy( fifo );

	return( 0 );
}

// Revisions:
//	$Log: queueTest1.c,v $
//	Revision 1.2  2014/10/13 11:21:22  csci243
//	updated to 64 bit pointer architecture
//
//	Revision 1.1  2013/10/29 19:07:57  csci243
//	Initial revision
//
