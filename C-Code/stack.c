#include <stdio.h>
#define max 30

// Define the stack structure containing an array and a top index
typedef struct{
    int data[max];
    int top;
} stack;

// Initialize an empty stack
void makenull_stack(stack *s) {
    s->top = max;
}

// Check if the stack is empty
int empty_stack(stack s) {
    return s.top == max;
}

// Check if the stack is full
int full_stack(stack s) {
    return s.top == 0;
}

// Retrieve the top element of the stack
int retrieve_top(stack *s) {
    if (!empty_stack(*s)) {
        return s->data[s->top];
    } else {
        printf("Stack is empty\n");
        return -1;  // Return an invalid value or error
    }
}

// Push an element into the stack
void push(stack *s, int x) {
    if (full_stack(*s)) {
        printf("Stack is full\n");
    } else {
        s->top--;  // Decrement top and then insert the element
        s->data[s->top] = x;
    }
}

// Pop an element from the stack
void pop(stack *s) {
    if (empty_stack(*s)) {
        printf("Stack is empty\n");
    } else {
        s->top++;  // Increment top to "remove" the element
    }
}

// Read elements into the stack
void read(stack *s) {
    printf("Enter number of elements:\n");
    int n, k;
    scanf("%d", &n);
    makenull_stack(s);
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &k);
        push(s, k);
    }
}

// Print the stack elements (from top to bottom)
void in(stack *s) {
    while (!empty_stack(*s)) {
        printf("%d\t", s->data[s->top]);  // Print the top element
        pop(s);  // Remove the top element
    }
}

int main() {
    stack s;
    read(&s);  // Pass the address of the stack
    in(&s);    // Pass the address of the stack
    return 0;
}
