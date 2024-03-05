#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *get_inputs(char* filename)// int* val_arr, int* x_arr, int* y_arr)
{
    int* val_arr = NULL;
    int* x_arr = NULL;
    int* y_arr = NULL;
    int* size = 0;
    FILE* fptr = fopen(filename, "r");     // Opening file and checking if its NULL or not

    if(fptr == NULL)
  {
    fclose(fptr);
    return NULL ; // Doesn't do anything if fptr is null
  }
  else
  {
    char line_length[100]; 
    int node_Count = 0; // Number of nodes in the fiole

    // Counting the total number of nodes in the file
    while(fgets(line_length, sizeof(line_length), fptr) != NULL)
    {
      node_Count++; 
    }

    // Allocating memory for the arrays that store the inputs
    val_arr = malloc(sizeof(int) * (node_Count)); 
    x_arr = malloc(sizeof(int) * (node_Count));
    y_arr = malloc(sizeof(int) * (node_Count));
    if(val_arr == NULL || x_arr == NULL || y_arr == NULL)
    {
      fclose(fptr);
      return NULL;
    }
    fseek(fptr, 0, SEEK_SET); // Resets pointer to the beginning of the file
    node_Count = 0; // Resets number of nodes
    while(fgets(line_length, sizeof(line_length), fptr) != NULL)
    {
      char type;
      int val, x, y;
      if(sscanf(line_length, "%d(%d,%d)\n", &val, &x, &y) == 3)
      {
        val_arr[node_Count] = val;
        x_arr[node_Count] = x;
        y_arr[node_Count] = y;
        node_Count++; // Incriments the index variable
      }
      else if (sscanf(line_length, "%c\n", &type) == 1)
      {
        val_arr[node_Count] = (int)type;
        x_arr[node_Count] = -1;
        y_arr[node_Count] = -1;
        node_Count++; // Incriments the index variable
      }
    }
    *size = node_Count;
    fclose(fptr);
  }
  return(buildTree(val_arr, x_arr, y_arr, size));
}

// Function that creates a new node in the tree
Node *createNode(int val, int x, int y)
{
  Node *node = (Node*)malloc(sizeof(Node));
  if((node) == NULL)
  {
    return(NULL);
  }
  node -> val = val; // Assigns node value to val
  node -> x = x; // Assigns packing width to x
  node -> y = y; // Assigns packing length to y
  node -> max_x = 0;
  node -> max_y = 0;
  node -> dim_x = 0;
  node -> dim_y = 0;
  node -> left = NULL; // Assigns left  subtree to be null for now
  node -> right = NULL; // Assigns right subtree to be null for now

  return node;
}

// Helper function that recursively builds tree
Node *buildTreeHelper(int* val_arr, int* x_arr, int* y_arr, int* index)
{
  Node* node = createNode(val_arr[*index], x_arr[*index], y_arr[*index]); // Creates Node

  if(x_arr[*index] == -1)
  {
    (*index)--;
    node ->right = buildTreeHelper(val_arr, x_arr, y_arr, index); // Recursively builds left subtree
    (*index)--;
    node ->left = buildTreeHelper(val_arr, x_arr, y_arr, index); // Recursively builds right subtree
  }
  ree(val_arr);
  free(x_arr);
  free(y_arr);
  return node;
}

// Function that returns the built tree
Node *buildTree(int* val_arr, int* x_arr, int* y_arr, int* size)
{
  int index = size - 1; // Initializes index variable to begin tree building
  return (buildTreeHelper(val_arr, x_arr ,y_arr, &index)); // Full tree building process that returns root node
}

// Function that prints out the postorder traversal of the tree to the output file
void preorderTraversal(Node *root, char* filename)
{
  FILE* fptr = fopen(filename, "a");
  if(fptr == NULL)
  {
    return;
  }
  else
  {
    if(root == NULL)
    {
      fclose(fptr);
      return;
    }
    preorderTraversal(root->left, filename); // Traverses through left subtrees
    preorderTraversal(root->right, filename); // Traverses through right subtrees
    if((root->left == NULL) && (root->right == NULL))
    {
      fprintf(fptr, "%d(%d,%d)\n", root->val, root->x, root->y); // Prints leaf node data
      //printf("%d(%d,%d)\n", root->val, root->x, root->y); // Prints leaf node data
    }
    else
    {
      fprintf(fptr, "%c\n", (char)(root->val)); // Prints internal node data

      //printf("%c\n", (char)(root->val));
    } 
  }
  fclose(fptr);

}


// Function for freeing all memory allocated to build the tree
void freeTree(Node* root)
{
  if(root != NULL)
  {
    freeTree(root-> left); // Frees left subtree recursively
    freeTree(root-> right); // Frees right subtree recursively 
    free(root); // Frees internal ndies in a recursive manner
  }
}
