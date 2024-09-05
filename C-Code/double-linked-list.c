#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to delete a node with a given value
void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;

    // Search for the node to be deleted
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    // If node not found
    if (temp == NULL) return;

    // If the node to be deleted is the head node
    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL)
            (*head)->prev = NULL;
    } else {
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
    }

    free(temp);
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display the linked list in reverse
void displayListReverse(struct Node* head) {
    struct Node* temp = head;
    if (temp == NULL) return;

    // Go to the last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Traverse backward
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printf("Doubly Linked List after inserting at the end:\n");
    displayList(head);

    insertAtBeginning(&head, 5);
    printf("Doubly Linked List after inserting at the beginning:\n");
    displayList(head);

    deleteNode(&head, 20);
    printf("Doubly Linked List after deleting a node with value 20:\n");
    displayList(head);

    printf("Doubly Linked List in reverse order:\n");
    displayListReverse(head);

    return 0;
}



===========================================

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *pNext;
    struct Node *pPrev;
} Node;

// Create Node
Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->pNext = NULL;
    node->pPrev = NULL;
    return node;
}

// Insert node at the beginning
void insertBegin(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->pNext = *head;
    (*head)->pPrev = newNode;
    *head = newNode;
}

// Insert node at the end
void insertEnd(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->pNext != NULL) {
        temp = temp->pNext;
    }
    temp->pNext = newNode;
    newNode->pPrev = temp;
}

// Delete node with a given value
void deleteNode(Node **head, int value) {
    Node *temp = *head;

    // If head is the node to be deleted
    if (temp != NULL && temp->data == value) {
        *head = temp->pNext;
        if (*head != NULL) {
            (*head)->pPrev = NULL;
        }
        free(temp);
        return;
    }

    // Search for the node to be deleted
    while (temp != NULL && temp->data != value) {
        temp = temp->pNext;
    }

    // Node with the value not found
    if (temp == NULL) return;

    // Node found
    if (temp->pNext != NULL) { // Not the last node
        temp->pNext->pPrev = temp->pPrev;
    }
    if (temp->pPrev != NULL) { // Not the first node
        temp->pPrev->pNext = temp->pNext;
    }

    free(temp);
}

// Display the list
void display(Node *head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->pNext;
    }
    printf("NULL\n");
}

// Display the list in reverse order
void displayListReverse(Node *head) {
    Node *temp = head;
    if (temp == NULL) return;

    // Go to the last node
    while (temp->pNext != NULL) {
        temp = temp->pNext;
    }

    // Traverse backward
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->pPrev;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    printf("Doubly Linked List after inserting at the end:\n");
    display(head);

    insertBegin(&head, 5);
    printf("Doubly Linked List after inserting at the beginning:\n");
    display(head);

    deleteNode(&head, 20);
    printf("Doubly Linked List after deleting a node with value 20:\n");
    display(head);

    printf("Doubly Linked List in reverse order:\n");
    displayListReverse(head);

    return 0;
}
