#include <stdio.h>

#define max 30

// Define the queue structure
typedef struct {
    int data[max];
    int Rear, Front;
} queue;

// Initialize an empty queue
void makenull_queue(queue *q) {
    q->Front = -1;
    q->Rear = -1;
}

// Check if the queue is empty
int empty_queue(queue q) {
    return q.Front == -1;
}

// Check if the queue is full
int full_queue(queue q) {
    return (q.Rear + 1) % max == q.Front;
}

// Add an element to the queue (enqueue)
void add_queue(queue *q, int x) {
    if (!full_queue(*q)) {
        if (empty_queue(*q)) {
            q->Front = 0;
        }
        q->Rear = (q->Rear + 1) % max;
        q->data[q->Rear] = x;
    } else {
        printf("Queue is full\n");
    }
}

// Remove an element from the queue (dequeue)
void delete_queue(queue *q) {
    if (!empty_queue(*q)) {
        if (q->Rear == q->Front) {
            makenull_queue(q);  // Reset the queue if it becomes empty
        } else {
            q->Front = (q->Front + 1) % max;
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
    makenull_queue(q);
    for (int i = 1; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &k);
        add_queue(q, k);
    }
}

// Print and empty the queue
void in(queue *q) {
    while (!empty_queue(*q)) {
        printf("%d  ", q->data[q->Front]);
        delete_queue(q);
    }
    printf("\n");
}

int main() {
    queue q;
    read(&q);
    in(&q);
    return 0;
}
