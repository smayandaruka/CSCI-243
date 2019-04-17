// Smayan Daruka
// sd9080
// Homework 5
// This is an implementation of a queue module.

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// structure definition
typedef struct queueStruct{
    void **elements;
    int numElements;
    int capacity;
    int (*cmp)(const void*a, const void*b);
} *QueueADT;

#define _QUEUE_IMPL_
#include "queueADT.h"

// defining the TRUE and FALSE to be used later in the program
#define TRUE 1
#define FALSE 0

// queue create function
QueueADT que_create( int (*cmp)(const void * a, const void * b) ){
    // dynamically creates the queue
    QueueADT queue = (QueueADT) malloc(sizeof(struct queueStruct));

    //initializes the queue to 0s if the queue is not initially null
    if(queue != NULL){
        queue->elements = NULL;
        queue->numElements = 0;
        queue->capacity = 0;
        queue->cmp = cmp;
    }
    return queue;
}

// queue destroy function
void que_destroy( QueueADT queue ){
    //checks if the queue is not empty and continues
    assert(queue != NULL);
    if(queue->elements != NULL)
        free(queue->elements); // frees/deallocates the memory

    free(queue);
}

// queue clear function
void que_clear( QueueADT queue ){
    if(queue->elements != NULL){
        free(queue->elements);
        queue->elements = NULL;
    }
    queue->numElements = 0;
    queue->capacity = 0;
}

// queue insert function..
// I applied a similar logic to some parts of this code from StackOverflow
void que_insert( QueueADT queue, void * data ){
    if(queue->elements == NULL){
        queue->elements = malloc(sizeof(struct queueStruct) * 10);
        assert(queue->elements != 0);
        queue->capacity = 10;
    }
    if(queue->numElements >= queue->capacity){
        // reallocates memory so as to make it bigger.. increases by 10 elements every time
        void* x = (void*)realloc(queue->elements, (queue->capacity + 10) * sizeof(struct queueStruct));
        assert(x != NULL); //asserts that memory was reallocated successfully
        queue->elements = x;
        queue->capacity += 10;
    }
    if (queue->cmp == NULL)
        queue->elements[queue->numElements] = data;
    else if (que_empty(queue) == TRUE)
        queue->elements[queue->numElements] = data;
    else{
        int count;
        for (count = 0; count < queue->numElements; ++count){
            if (queue->cmp(queue->elements[count], data) >= 0){
                if (count < (queue->numElements - 1)){
                    for (int i = queue->numElements; i > count; --i){
                        queue->elements[i] = queue->elements[i - 1];
                    }
                    queue->elements[count] = data;
                }
                else{
                    queue->elements[count + 1] = queue->elements[count];
                    queue->elements[count] = data;
                }
                break;
            }
        }
        if(count == queue->numElements)
            queue->elements[queue->numElements] = data;
    }
    queue->numElements += 1;
}

// queue remove function
void * que_remove( QueueADT queue ){
    assert(queue->numElements > 0);
    void *value = queue->elements[0];
    for(int count = 0; count < queue->numElements; ++count){
        queue->elements[count] = queue->elements[count + 1];
        queue->elements[count + 1] = NULL;
    }
    queue->numElements -= 1;

    return value;
}

// queue empty function
bool que_empty( QueueADT queue ){
    if(queue->numElements == 0)
        return TRUE;
    else
        return FALSE;
}
