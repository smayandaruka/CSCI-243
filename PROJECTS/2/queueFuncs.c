// Smayan Daruka
// sd9080
// Project 2 - Offspring
// queueFuncs.c - Source file containing function declarations

#include <stdlib.h>
#include "queueFuncs.h"

// initialize_queue function initializes the queue and returns a queue pointer
// there are no arguments passed into it
queue* initialize_queue(){
    // dynamically makes a queue
    queue* cur_queue = malloc(sizeof(queue));
    // checks if the queue was allocated successfully
    if(cur_queue != NULL){
        cur_queue->front = NULL;
        cur_queue->back = NULL;
        cur_queue->queueCount = 0;
    }
    return cur_queue;
}

// enqueue function adds an element to the queue
// it takes in a queue pointer, a pointer of the element to be inserted, and the priority of the element
void enqueue(queue* cur_queue, void* cur_data, int cur_priority){
    // dynamically creates a node structure
    node* cur_node = malloc(sizeof(node));
    node* tempNode;
    cur_node->data = cur_data;
    cur_node->next = NULL;
    cur_node->priority = cur_priority;
    // checks if there are elements in the queue
    if(cur_queue->queueCount != 0){
        // checks if the element's priority is lower than the first element of the queue
        if(cur_priority < cur_queue->front->priority){
            cur_node->next = cur_queue->front;
            cur_queue->front = cur_node;
        }
        // checks if the element's priority is higher than the last element of the queue
        else if(cur_priority >= cur_queue->back->priority){
            cur_queue->back->next = cur_node;
            cur_queue->back = cur_node;
        }
        else{
            // sets the pointer to the front of the queue
            tempNode = cur_queue->front;
            // traverses the queue
            while(tempNode != NULL){
                if(cur_priority < tempNode->next->priority){
                    cur_node->next = tempNode->next;
                    tempNode->next = cur_node;
                    break;
                }
                tempNode = tempNode->next;
            }
        }
    }
    // no elements are present in the queue
    else
        cur_queue->front = cur_queue->back = cur_node;
    // increments the queueCount counter
    cur_queue->queueCount++;
}

// dequeue function takes an element off of the queue
// it takes in a queue pointer
void* dequeue(queue* cur_queue){
    node* cur_node = cur_queue->front;
    void* data = NULL;
    // checks if there are elements in the queue
    if(cur_queue->queueCount != 0){
        cur_queue->front = cur_queue->front->next;
        // if there is only 1 element in the queue
        if(cur_queue->queueCount == 1){
            cur_queue->back = NULL;
            cur_queue->front = NULL;
        }
        data = cur_node->data;
        // after removing element, it decrements the queueCount variable
        (cur_queue->queueCount)--;
        // frees the memory
        free(cur_node);
        return data;
    }
    else
        return data;
}

// destroy_queue function destroys the queue and frees memory
// it takes in a queue pointer
void destroy_queue(queue* cur_queue){
    // runs as long as there are elements present
    while(cur_queue->queueCount != 0)
        dequeue(cur_queue);
    // frees the memory
    free(cur_queue);
}
