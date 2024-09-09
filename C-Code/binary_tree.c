#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node in the binary tree
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the binary tree (binary search tree logic)
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        // If the tree is empty, create the root node
        root = createNode(data);
    } else if (data < root->data) {
        // Insert into the left subtree if the data is smaller
        root->left = insertNode(root->left, data);
    } else {
        // Insert into the right subtree if the data is larger
        root->right = insertNode(root->right, data);
    }
    return root;
}

// In-order traversal (left -> root -> right)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Pre-order traversal (root -> left -> right)
void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Post-order traversal (left -> right -> root)
void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to search for a node in the tree
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return searchNode(root->left, key);
    } else {
        return searchNode(root->right, key);
    }
}

int main() {
    Node* root = NULL;
    
    // Insert elements into the binary tree
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);

    printf("In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Searching for a node
    int key = 40;
    Node* found = searchNode(root, key);
    if (found != NULL) {
        printf("Node with data %d found.\n", found->data);
    } else {
        printf("Node with data %d not found.\n", key);
    }

    return 0;
}
