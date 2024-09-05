// ONE THREAD
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function with the correct signature
void *printMsg(void *arg) {
  char *str = (char *)arg; // Cast the argument to the correct type
  printf("Thread id %ld: %s\n", pthread_self(), str);
 
  pthread_exit(NULL);
}

int main() {
  pthread_t thread_id;
  char *str = "hello kitty!"; // Fixed typo in the string
  printf("Before Thread\n");

  // Create the thread
  if (pthread_create(&thread_id, NULL, printMsg, (void *)str) != 0) {
    perror("Failed to create thread");
    exit(EXIT_FAILURE);
  }

  // Wait for the thread to complete

  if (pthread_join(thread_id, NULL) != 0) {
    perror("Failed to join thread");
    exit(EXIT_FAILURE);
  }

  printf("After Thread\n");
  return 0; // No need to call exit(0) explicitly; return from main will do
}

//MULTIPBLE THREAD
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5 // Number of threads to create

// Thread function with the correct signature
void *printMsg(void *arg) {
  char *str = (char *)arg; // Cast the argument to the correct type
  printf("Thread ID %lu: %s\n", (unsigned long)pthread_self(), str);
  pthread_exit(NULL);
}

int main() {
  pthread_t thread_ids[NUM_THREADS];
  char *messages[NUM_THREADS] = {"Hello from thread 1!", "Hello from thread 2!",
                                 "Hello from thread 3!", "Hello from thread 4!",
                                 "Hello from thread 5!"};
  int i;

  printf("Before Threads\n");

  // Create threads
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&thread_ids[i], NULL, printMsg, (void *)messages[i]) !=
        0) {
      perror("Failed to create thread");
      exit(EXIT_FAILURE);
    }
  }

  // Wait for all threads to complete
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(thread_ids[i], NULL) != 0) {
      perror("Failed to join thread");
      exit(EXIT_FAILURE);
    }
  }

  printf("After Threads\n");
  return 0; // No need to call exit(0) explicitly; return from main will do
}



//SOME COMMOND FUNCTION THREAD

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg) {
  // detach the current thread
  // from the calling thread
  pthread_detach(pthread_self());

  printf("Inside the thread\n");

  // exit the current thread
  pthread_exit(NULL);
}

void fun() {
  pthread_t ptid;

  // Creating a new thread
  pthread_create(&ptid, NULL, &func, NULL);
  printf("This line may be printed"
         " before thread terminates\n");

  // The following line terminates
  // the thread manually
  // pthread_cancel(ptid);

  // Compare the two threads created
  if (pthread_equal(ptid, pthread_self()))
    printf("Threads are equal\n");
  else
    printf("Threads are not equal\n");

  // Waiting for the created thread to terminate
  pthread_join(ptid, NULL);

  printf("This line will be printed"
         " after thread ends\n");

  pthread_exit(NULL);
}

// Driver code
int main() {
  fun();
  return 0;
}


//MUTEX IN THREAD
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Define the number of threads
#define NUM_THREADS 5

// Shared resource
int counter = 0;

// Mutex for synchronizing access to the shared resource
pthread_mutex_t counter_mutex;

// Thread function
void* incrementCounter(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 1000; i++) {
        // Lock the mutex before accessing the shared resource
        pthread_mutex_lock(&counter_mutex);
        
        // Critical section: accessing and modifying the shared resource
        counter++;
        printf("Thread %d: counter = %d\n", id, counter);
        
        // Unlock the mutex after accessing the shared resource
        pthread_mutex_unlock(&counter_mutex);
        
        // Sleep for a short time to simulate work
        usleep(10);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&counter_mutex, NULL) != 0) {
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i + 1;
        if (pthread_create(&threads[i], NULL, incrementCounter, &threadIds[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    printf("Final counter value: %d\n", counter);
    return 0;
}
