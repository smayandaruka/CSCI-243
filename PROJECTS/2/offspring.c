// Smayan Daruka
// sd9080
// Project 2 - Offspring

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trimit.h"
#include "queueFuncs.h"

// NTree_S implementation for N-ary tree structure.
typedef struct NTree_S{
    char* name;                  // Name of the person
    struct NTree_S** children;   // collection of children
    size_t child_count;          // current number of children
    size_t capacity;             // capacity of children collection
} NTree;

// priority_queue function prioritizes the elements of the tree
void priority_queue(NTree* tree, queue* cur_queue, int priority){
    // checks if the tree is not empty
    if(tree != NULL){
        // calls the enqueue function to push the element into the queue based on priority
        enqueue(cur_queue, tree, priority);
        for(size_t i = 0; i < tree->child_count; i++){
            // keeps calling itself for the duration of the for loop
            priority_queue(tree->children[i], cur_queue, (priority + 1));
        }
    }
}

// find_node function finds a given name in the tree and returns the node pointer
NTree* find_node(NTree* tree, char name[]){
    int size, count;
    // This variable is a pointer to where that particular element is
    NTree* node_pointer = NULL;
    NTree* tempTree;
    // creates a queue structure and initializes it
    queue* cur_queue = initialize_queue();
    priority_queue(tree, cur_queue, 0);
    // size holds the number of elements in the queue
    size = cur_queue->queueCount;
    for(count = 0; count < size; count++){
        tempTree = dequeue(cur_queue);
        // compares the name passed into the function with the name in the tree and returns the position
        if(strcmp(name, tempTree->name) == 0){
            node_pointer = tempTree;
            break; // breaks out of the for loop once the name is found
        }
    }
    // frees the memory and destroys the queue
    destroy_queue(cur_queue);
    return node_pointer;
}

// add_child function adds an element into the tree
NTree* add_child(NTree* tree, char parent_name[], char child_name[]){
    // checks if the tree is empty indicating a new tree will need to be made
    if(tree == NULL){
        char* parent = malloc(strlen(parent_name) + 1);
        strcpy(parent, parent_name);
        // dynamically creates a tree
        tree = malloc(sizeof(NTree));
        tree->name = parent;
        tree->children = NULL;
        tree->child_count = 0;
        tree->capacity = 0;
    }
    // If child_name is not null
    if(child_name != NULL){
        // finds where the parent is located
        NTree* tempTree = find_node(tree, parent_name);
        if(tempTree != NULL){
            for(size_t i = 0; i < tempTree->child_count; i++){
                // if the child is already in the tree, return
                if(strcmp(child_name, tempTree->children[i]->name) == 0)
                    return tree;
            }
            char* child = malloc(strlen(child_name)+1);
            strcpy(child, child_name);
            // increments the child_count counter
            tempTree->child_count++;
            // reallocates memory
            tempTree->children = realloc(tempTree->children, (sizeof(NTree) * (tempTree->child_count)));
            NTree* newChild = malloc(sizeof(NTree));
            // if newChild is not null
            if(newChild != NULL){
                newChild->name = child;
                newChild->children = NULL;
                newChild->child_count = 0;
                newChild->capacity = 0;
            }
            // sticks it to the end of the list
            tempTree->children[(tempTree->child_count) - 1] = newChild;
        }
        // compares name of parent in the tree to name of child
        else if(strcmp(tree->name, child_name) == 0){
            // dynamically creates a tree
            NTree* tempTree = malloc(sizeof(NTree));
            if(tempTree != NULL){
                char* parent = malloc(strlen(parent_name) + 1);
                strcpy(parent, parent_name);
                tempTree->name = parent;
                tempTree->child_count = 1;
                tempTree->children = malloc((sizeof(tree) * (tempTree->child_count)));
                tempTree->children[0] = tree;
                tempTree->capacity = 1;
                return tree;
            }
        }
        // names could not be added to the tree. print error message
        else{
            fprintf(stderr,"error: '%s' is not in the tree and '%s' is not the root.\n", parent_name, child_name);
            // frees the memory
            free(tempTree);
        }
    }
    return tree;
}

// print_tree function prints the tree depending on the nature of how it is called
void print_tree(NTree* tree, int num){
    // creates a queue structure and prioritizes it
    queue* cur_queue = initialize_queue();
    priority_queue(tree, cur_queue, 0);
    NTree* cur_tree;
    // checks if the queue is not empty
    while(cur_queue->queueCount != 0){
        cur_tree = dequeue(cur_queue);
        // prints the name of the parent
        printf("%s had ", cur_tree->name);
        // checks if there are children
        if(cur_tree->child_count != 0){
            for(size_t i = 0; i < cur_tree->child_count; i++){
                // there is only 1 child
                if(cur_tree->child_count == 1)
                    printf("%s.\n", cur_tree->children[i]->name);
                // printing the name of the last child
                else if(i == cur_tree->child_count - 1)
                    printf(" and %s.\n", cur_tree->children[i]->name);
                // printing the name of the second child
                else if(i == 0)
                    printf("%s", cur_tree->children[i]->name);
                // prints multiple names indicating multiple children
                else
                    printf(", %s", cur_tree->children[i]->name);
            }
            // exits the function if num is 1 implying it was called from find and we don't need to print the entire tree
            if(num == 1)
                return;
        }
        // the parent had no children
        else
            printf("no offspring.\n");
    }
    // destroys the queue and frees the memory
    destroy_queue(cur_queue);
}

// destroy_tree function destroys the current tree
void destroy_tree(NTree* cur_tree){
    NTree* temp;
    // creates a queue structure and initializes it
    queue* cur_queue = initialize_queue();
    priority_queue(cur_tree, cur_queue, 0);
    //checks if the queue is not empty
    while(cur_queue->queueCount != 0){
        // dequeues an element
        temp = dequeue(cur_queue);
        // frees memory
        free(temp->name);
        free(temp->children);
        free(temp);
    }
    // destroys the queue and frees the memory
    destroy_queue(cur_queue);
}

int main(int argc, char* argv[]){
    NTree* tree = NULL;
    NTree* nodePtr = NULL;
    // used to store user entered input at command line
    char input[1024];
    char command[1024];
    // variables to hold the names, size, and height
    char* parent_name = NULL;
    char* child_name = NULL;
    char* name;
    int printSize = 0;
    int printHeight = 0;

    // checks if there was a command line argument indicating an input file is present
    if(argc > 1){
        FILE* fp;
        // opens the file in read-only mode
        fp = fopen(argv[1], "r");
        if(fp != NULL){
            //Read file line by line
            while(fgets(input, 1024, fp)){
                // tokenizing the input
                parent_name = strtok(input, ",");
                memmove(parent_name, trim(parent_name), strlen(trim(parent_name)) + 1);
                if(parent_name != NULL){
                    // adds the element to the tree
                    tree = add_child(tree, parent_name, child_name);
                    child_name = strtok(NULL, ",");
                    while(child_name != NULL){
                        // trims the child name to remove white-spaces
                        memmove(child_name, trim(child_name), strlen(trim(child_name)) + 1);
                        tree = add_child(tree, parent_name, child_name);
                        child_name = strtok(NULL, ",");
                    }
                }
            }
            // closes the file
            fclose(fp);
        }
        // the file could not be opened for reading
        else
            fprintf(stderr, "error: could not open file '%s'\n", argv[1]);
    }
    // runs forever until user types quit
    while(1){
        // user prompt
        printf("offspring> ");
        // reads in the input
        fgets(input, 1024, stdin);
        // tokenizes the input and copies it into command
        strcpy(command, strtok(input, " ,"));
        // trims white-spaces
        memmove(command, trim(command), strlen(trim(command)) + 1);

        // ADD
        if(strcmp(command, "add") == 0){
            // tokenizes the input
            parent_name = strtok(NULL, ",");
            // checks if there is a parent name
            if(parent_name != NULL){
                // trims white-spaces
                memmove(parent_name, trim(parent_name), strlen(trim(parent_name)) + 1);
                child_name = strtok(NULL, ",");
                // checks if there is a child name
                if(child_name != NULL){
                    memmove(child_name, trim(child_name), strlen(trim(child_name)) + 1);
                    tree = add_child(tree, parent_name, child_name);
                }
                // user entered incorrect input. prints usage message
                else
                    fprintf(stderr, "Usage: 'add parent name , child name'\n");
            }
            // user entered incorrect input. prints usage message
            else
                fprintf(stderr, "Usage: 'add parent name , child name'\n");
        }

        // FIND
        if(strcmp(command, "find") == 0){
            // tokenizes the input
            name = strtok(NULL, ",");
            // checks if the name is not null
            if(name != NULL){
                // trims the white-spaces
                memmove(name, trim(name), strlen(trim(name)) + 1);
                // finds where the name is in the tree
                nodePtr = find_node(tree, name);
                // if the name exists
                if(nodePtr != NULL)
                    print_tree(nodePtr, 1);
                else
                    fprintf(stderr, "error: '%s' not found\n", name);
            }
            // checks if the tree is empty
            else if(name == NULL && tree == NULL)
                fprintf(stderr, "error: '%s' not found\n", name);
        }

        // PRINT
        if(strcmp(command, "print") == 0){
            // tokenizes the input
            name = strtok(NULL, ",");
            // checks if the user entered a specific name and it's not empty
            if(name != NULL){
                // trims the white-spaces
                memmove(name, trim(name), strlen(trim(name)) + 1);
                // finds where the name is in the tree
                nodePtr = find_node(tree, name);
                // if the name exists
                if(nodePtr != NULL)
                    print_tree(nodePtr, 0);
                // name does not exist
                else
                    fprintf(stderr, "error: '%s' not found\n", name);
            }
            else if(name == NULL && tree == NULL)
                fprintf(stderr, "error: '%s' not found\n", name);
            // no name was specified and this prints the entire tree
            else
                print_tree(tree, 0);
        }

        // SIZE
        if(strcmp(command, "size") == 0){
            // tokenizes the input
            name = strtok(NULL, ",");
            // creates and initializes a queue
            queue* q = initialize_queue();
            // checks if the name is not null
            if(name != NULL){
                // trims the white-spaces
                memmove(name, trim(name), strlen(trim(name)) + 1);
                // finds where the name is in the tree
                nodePtr = find_node(tree, name);
                // prioritizes the queue
                priority_queue(nodePtr, q, 0);
                printSize = q->queueCount;
                // if the name exists
                if(nodePtr != NULL)
                    printf("size: %d\n",printSize);
                else
                    printf("size: %d\n", printSize);
            }
            else if(tree != NULL){
                priority_queue(tree, q, 0);
                printSize = q->queueCount;
                printf("size: %d\n", printSize);
            }
            else if(tree == NULL){
                printSize = 0;
                printf("size: %d\n", printSize);
            }
            // destroys the queue and frees memory
            destroy_queue(q);
        }

        // HEIGHT
        if(strcmp(command, "height") == 0){
            // tokenizes the input
            name = strtok(NULL, ",");
            // creates and initializes a queue
            queue* q = initialize_queue();
            // checks if the name is not null
            if(name != NULL){
                // trims the white-spaces
                memmove(name, trim(name), strlen(trim(name)) + 1);
                // finds where the name is in the tree
                nodePtr = find_node(tree, name);
                // if the name exists
                if(nodePtr != NULL){
                    // prioritizes the queue
                    priority_queue(nodePtr, q, 0);
                    printHeight = q->back->priority;
                    printf("height: %d\n",printHeight);
                }
                // prints the height of a non-existent person
                else
                    printf("height: %d\n", -1);
            }
            else{
                if(tree == NULL)
                    printf("height: %d\n", -1);
                else{
                    // prioritizes the queue
                    priority_queue(tree, q, 0);
                    printHeight = q->back->priority;
                    printf("height: %d\n", printHeight);
                }
            }
            // destroys the queue and frees the memory
            destroy_queue(q);
        }

        // INIT
        if(strcmp(command, "init") == 0){
            // destroys the tree and frees the memory
            destroy_tree(tree);
            tree = NULL;
        }

        // HELP
        if(strcmp(command, "help") == 0){
            fprintf(stderr, "User Commands for offspring:\n");
            fprintf(stderr, "add parent-name, child-name # find parent and add child.\n");
            fprintf(stderr, "find name     # search and print name and children if name is found.\n");
            fprintf(stderr, "print [name]  # breadth first traversal of offspring from name.\n");
            fprintf(stderr, "size [name]   # count members in the [sub]tree.\n");
            fprintf(stderr, "height [name] # return the height of [sub]tree.\n");
            fprintf(stderr, "init          # delete current tree and restart with an empty tree.\n");
            fprintf(stderr, "help          # print this information.\n");
            fprintf(stderr, "quit          # delete current tree and end program.\n");
        }

        // QUIT
        if(strcmp(command, "quit") == 0){
            // Destroys the tree, frees the memory, and exits the program
            destroy_tree(tree);
            printf("\n");
            return 0;
        }
    }
}
