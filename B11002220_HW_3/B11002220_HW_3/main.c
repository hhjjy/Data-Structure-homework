/**
 * @file BST.c
 * @author Leo (you@domain.com)
 * @brief HW3 BST
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#define __PRINTF_TO_FILE__BY_VISUAL_STUDIO

#include "useful.h"
typedef struct node *treePointer;
typedef struct node
{
    int data;
    treePointer left;
    treePointer right;
} Node;
treePointer createNode(char data)
{
    treePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/**
 * @brief Delete leaf nodes in a binary tree.
 * @param root The root node of the binary tree.
 * @param level it save the current root's level . 
 * @return treePointer The modified root node of the binary tree.  
 */
treePointer deleteLeaf(treePointer root,int level)
{
    if (root)
    {
        if (root->left == NULL && root->right == NULL && level!= 0) // Check if it is a leaf node
        {
            free(root);  // Free the memory space of the leaf node
            return NULL; // Return a null pointer to indicate the deletion of the leaf node
        }
        // Recursively delete leaf nodes in the left subtree and right subtree
        root->left = deleteLeaf(root->left,level+1);
        root->right = deleteLeaf(root->right, level + 1);
    }
    return root; // Return the modified root node of the binary tree
}

/**
 * @brief Insert a node at the specified position.
 *
 * @param root The current node.
 * @param data The character data to be inserted.
 * @return treePointer
 * @note: There are two possible situations that can occur.
 *          1. Return the address of the new node if the root node is empty!
 *          2. Return root to pass the previously  address to root->right or root->left.
 */
treePointer insertNode(treePointer root, char data)
{
    // Handle the case where the current node is empty
    if (root == NULL)
    {
        return createNode(data);
    }
    // Search to the right
    if (root->data < data)
    {
        root->right = insertNode(root->right, data);
    }
    // Search to the left
    if (root->data > data)
    {
        root->left = insertNode(root->left, data);
    }
    // Make sure that right & left store the current root node to connect successfully
    return root;
}

/**
 * @brief Search for a node containing the specified data in a binary search tree.
 * @param root The root node of the binary search tree.
 * @param data The data to search for.
 * @return treePointer a pointer to the node containing the search data, or NULL if not found.
*/
treePointer search(treePointer root, char data)
{
    if (!root || root->data == data) // if current node or data find then return current node   
        return root;
    if (root->data < data) // search from right 
        return search(root->right, data);
    else // search from left 
        return search(root->left, data);
}
/**
 * @brief Perform an inorder traversal of a binary tree.
 *
 * @param root The root node of the binary tree.
 * @return void
 */
void inorderTraversal(treePointer root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%c", root->data);
        inorderTraversal(root->right);
    }
}

void printTree(treePointer root, int level)
{
    if (root == NULL)
    {
        return;
    }

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%c\n", root->data);

    printTree(root->left, level + 1);
}
int main()
{
    clear_file();
    // Set input file 
    FILE* inputFile;
    if (fopen_s(&inputFile, "Input.txt", "r") != 0)
    {
        fprintf(stderr, "Failed to open Input.txt\n");
        return 1;
    }

    // Read each line
    char line[100];
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        line[strcspn(line, "\n")] = '\0'; // delete  \n 
        treePointer BST = NULL;
        // Read a char and send it into BST 
        // first opeation 
        for (int i = 0; line[i]; i++)
        {
            BST = insertNode(BST, line[i]);
        }
        inorderTraversal(BST); 
        printf("\n");
        // second opeartion 
        deleteLeaf(BST,0); 
        inorderTraversal(BST);
        printf("\n");
    }
    fclose(inputFile);
    return 0;
}