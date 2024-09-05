#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
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
}

// Function to delete a node with a given value
void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head = temp->next;  // Changed head
        free(temp);           // Free old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in the list
    if (temp == NULL) return;

    // Unlink the node from the linked list
    prev->next = temp->next;

    free(temp);  // Free memory
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printf("Linked List after inserting at the end:\n");
    displayList(head);

    insertAtBeginning(&head, 5);
    printf("Linked List after inserting at the beginning:\n");
    displayList(head);

    deleteNode(&head, 20);
    printf("Linked List after deleting a node with value 20:\n");
    displayList(head);

    return 0;
}



==================================================


/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *pNext;
}Node;
//create Node
Node *createNode(int value){
    Node *node = (Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->pNext = NULL;
    return node;
}
//insert node at begin
void insertBegin(Node **head, int value){
    Node *newNode = createNode(value);
    if(*head==NULL){
        *head = newNode;
        return;
    }
    newNode->pNext = *head;
    *head = newNode;
}
//insert node at end
void insertEnd(Node **head, int value){
    Node *newNode = createNode(value);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    Node *temp = *head;
    while(temp->pNext!=NULL){
        temp=temp->pNext;
    }
    temp->pNext = newNode;
}
//delete node given value
void deleteNode(Node **head, int value){
    Node *temp = *head;
    Node *prev = NULL;
    //if head is node need to delete
    if(temp!=NULL && temp->data == value) {
        *head = temp->pNext;
        free(temp);
        return;
    }
    //search find key and keep track prev node
    while(temp!=NULL && temp->data!= value){
        prev=temp;
        temp=temp->pNext;
    }
    if(temp==NULL)return; //node not found
    
    //value found
    prev->pNext = temp->pNext;
    free(temp);
}

//display list node
void display(Node *head){
    while(head!=NULL){
        printf("%d->", head->data);
        head = head->pNext;
    }
    printf("NULL\n");
}

int main()
{
    
    Node* head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    printf("Linked List after inserting at the end:\n");
    display(head);

    insertBegin(&head, 5);
    printf("Linked List after inserting at the beginning:\n");
    display(head);

    deleteNode(&head, 20);
    printf("Linked List after deleting a node with value 20:\n");
    display(head);
    return 0;
}
