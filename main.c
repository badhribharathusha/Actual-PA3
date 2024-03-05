// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char* argv[])
{
    if (argc != 5) {
        return EXIT_FAILURE;
    }

    Node* root = get_inputs(argv[1]);
    
        //Outputs
        preorderTraversal(root, argv[2]);
        Node_Coordinates(root, argv[3]);
        Node_Dimensions(root, argv[4]);

        // Frees all memory that has been allocated 
        freeTree(root);

        return 0;


    
    
}