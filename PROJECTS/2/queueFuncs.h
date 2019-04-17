// Smayan Daruka
// sd9080
// Project 2 - Offspring
// queueFuncs.h - Header file containing function prototypes

#ifndef queueFuncs_H
#define queueFuncs_H

// linked list implementation of the queue
typedef struct node_s{
    void* data;
    struct node_s* next;
    int priority;
} node;

// queue structure
typedef struct queueStruct{
    node* back;
    node* front;
    int queueCount;
} queue;

// initialize the queue
queue* initialize_queue();

// add elements into the queue
void enqueue(queue* q, void* data, int priority);

// remove elements from the queue
void* dequeue(queue* q);

// destroy the queue
void destroy_queue(queue* q);

#endif
