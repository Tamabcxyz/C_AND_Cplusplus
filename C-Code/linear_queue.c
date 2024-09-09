#include <stdio.h>

#define max 30

// Define the queue structure with front and rear
typedef struct {
    int data[max];
    int front, rear;
} queue;

// Initialize an empty queue
void makenull(queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int empty(queue q) {
    return q.front == -1;
}

// Check if the queue is full
int full(queue q) {
    return (q.rear + 1) % max == q.front;
}

// Add an element to the end of the queue (enqueue)
void endqueue(queue *q, int x) {
    if (!full(*q)) {
        if (empty(*q)) {
            q->front = 0;
        }
        q->rear = (q->rear + 1) % max; // Circular increment
        q->data[q->rear] = x;
    } else {
        printf("Queue is full\n");
    }
}

// Remove an element from the front of the queue (dequeue)
void dequeue(queue *q) {
    if (!empty(*q)) {
        if (q->front == q->rear) {
            // Queue becomes empty after this dequeue
            makenull(q);
        } else {
            q->front = (q->front + 1) % max; // Circular increment
        }
    } else {
        printf("Queue is empty\n");
    }
}

// Read elements into the queue
void read(queue *q) {
    int n, k;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    makenull(q);
    for (int i = 1; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &k);
        endqueue(q, k);
    }
}

// Print the queue elements and dequeue them
void in(queue *q) {
    while (!empty(*q)) {
        printf("%d\t", q->data[q->front]);
        dequeue(q);
    }
    printf("\n");
}

int main() {
    queue q;
    read(&q);
    in(&q);
    return 0;
}
