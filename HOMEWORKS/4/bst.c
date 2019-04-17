//name: Smayan Daruka
//username: sd9080

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// FUNCTIONS STUDENTS ARE REQUIRED TO IMPLEMENT

// my own function for adding elements to the tree.
void insert_tree(TreeNode** root, int data){
    if(*root == NULL){ // checks if root is null implying the tree is empty
        *root = malloc(sizeof(TreeNode)); // allocates memory using malloc for the root
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if(data < (*root)->data) // if the number is smaller than current element
        insert_tree(&((*root)->left), data);
    else if(data > (*root)->data) // if number is greater than current element
        insert_tree(&((*root)->right), data);
}

/// build_tree()
///     Dynamically build BST by allocating nodes on the heap.
///     The client passes the address of storage that will hold
///     the pointer to the root tree node. The function then
///     dynamically allocates the nodes as it builds the binary
///     search tree which holds the elements.
///
/// args -
///        root - a pointer to the pointer to the root of the tree
///               to build this tree on to.
///        elements - array of integers to add to the tree
///        count - the number of integers in the array
void build_tree(TreeNode** root, const int elements[], const int count){
    // This calls the insert functions "count" number of times. count implying how many integers there are.
    // The insert_tree function actually adds to the tree.
    for(int i = 0; i < count; i++)
        insert_tree(root, elements[i]);
}

/// traverse()
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// args -
///        root - a pointer to the root of the tree to traverse
///        type - the traversal type
void traverse(const TreeNode* root, const TraversalType type){
    // if the tree is not empty
    if(root != NULL){
        // Recursive preorder traversal of the tree
        if(type == 0){
            printf("%i\n", (root)->data);
            traverse((root)->left, PREORDER);
            traverse((root)->right, PREORDER);
        }
        // Recursive inorder traversal of the tree
        else if(type == 1){
            traverse((root)->left, INORDER);
            printf("%i\n", (root)->data);
            traverse((root)->right, INORDER);
        }
        // Recursive postorder traversal of the tree
        else if(type == 2){
            traverse((root)->left, POSTORDER);
            traverse((root)->right, POSTORDER);
            printf("%i\n", (root)->data);
        }
    }
}

/// cleanup_tree()
///    Cleanup all memory associated with the nodes on the heap.
///
/// args -
///      root - the current root of the tree
void cleanup_tree(TreeNode* root){
    if(root != NULL){
        // recursively cleans up the tree
        cleanup_tree((root)->left);
        cleanup_tree((root)->right);
        // frees the memory
        free(root);
    }
}

int main(int argc, char* argv[]){
    int numOfIntegers = 0; // to store the actual number of integers stored
    int bufNum = 0; // buffer variable to store the number of integers
    int* elements; // array to hold the integers entered

    // argc should be equal to 2 implying the filename and 1 command-line argument
    if(argc != 2){
        printf("Usage: bst #\n");
        return 0;
    }
    else{
        bufNum = strtol(argv[1], NULL, 10); // store the number of integers entered into the buffer variable to test later
        if(bufNum < 0){
            printf("# must be greater than 0\n");
            return 0;
        }
        else{
            numOfIntegers = bufNum; // after verifying the value in the buffer variable, it is assigned to the actual variable.
            elements = (int*) malloc(sizeof(int) * numOfIntegers); // allocates enough memory to hold the specified number of integers in the array

            printf("Enter %d integer values to place in tree:\n", numOfIntegers);

            // Reads every integer and stores it in the array
            for(int i = 0; i < numOfIntegers; i++)
                scanf("%i", &elements[i]);

            //Prints the integers entered as is.
            printf("Input values:\n");
            for(int i = 0; i < numOfIntegers; i++)
                printf("%i\n", elements[i]);

        // Creates the initial root
        TreeNode* root = NULL;
        build_tree(&root, elements, numOfIntegers);

        printf("Preorder:\n");
        traverse(&(*root), PREORDER);

        printf("Inorder:\n");
        traverse(&(*root), INORDER);

        printf("Postorder:\n");
        traverse(&(*root), POSTORDER);

        // frees the dynamically allotted array
        free(elements);

        cleanup_tree(&(*root));

        }
        return 0;
    }
}
