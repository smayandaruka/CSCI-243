// File: $Id: bst.h,v 1.3 2016/03/11 16:28:38 csci243 Exp $
//
// Binary Search Tree structure and function declarations 
//
// @author: sps
// @author: rwd

#ifndef BST_H
#define BST_H

/// The definition of the tree structure
typedef struct TreeNode {
    int data ;                  // the data stored in the node
    struct TreeNode * left ;     // node's left child
    struct TreeNode * right ;    // node's right child
} TreeNode;

/// The three supported traversals
typedef enum {
    PREORDER,           // parent -> left -> right
    INORDER,            // left -> parent -> right
    POSTORDER           // left -> right -> parent
} TraversalType;

// FUNCTIONS STUDENTS ARE REQUIRED TO IMPLEMENT

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
void build_tree(TreeNode** root, const int elements[], const int count);

/// traverse()
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// args -
///        root - a pointer to the root of the tree to traverse
///        type - the traversal type
void traverse(const TreeNode* root, const TraversalType type);

/// cleanup_tree()
///    Cleanup all memory associated with the nodes on the heap.
///
/// args -
///      root - the current root of the tree
void cleanup_tree(TreeNode* root);

#endif // BST_H

