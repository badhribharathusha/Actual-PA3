// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    char type;          // Type of node(leaf or internal)
    int val;            // Value of node
    int x;              // width of node
    int y;              // height of node
    int max_x;          // max x width
    int max_y;          // max y height
    int dim_x;          // Last output file x dimmension
    int dim_y;          // Last output file y dimmension
    struct _Node *left;  // Pointer to left child node
    struct _Node *right; // Pointer to right child node
} Node;

//void get_inputs(char* filename, int* val_arr, int* x_arr, int* y_arr);
Node *get_inputs(char* filename);
void freeTree(Node *root);
Node *buildTreeHelper(int* val_arr, int* x_arr, int* y_arr, int* index);
Node *createNode(int val, int x, int y);
Node *buildTree(int* val_arr, int* x_arr, int* y_arr, int* size);
void preorderTraversal(Node *root, char* filename);
void Node_Coordinates(Node *root, char* filename );
void Node_Dimensions(Node *root, char* filename );
