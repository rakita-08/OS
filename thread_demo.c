#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to be executed by the thread
void* threadFunction(void* arg) {
    printf("Thread started. Thread ID: %lu\n", pthread_self());
    printf("Hello from the thread!\n");
    sleep(2);  // Simulate work
    printf("Thread is terminating.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    printf("Main process (PID: %d) creating a thread...\n", getpid());

    // Create a new thread
    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    printf("Thread has terminated. Main process continues.\n");
    printf("Main process exiting.\n");
    printf("Name:Rakita Rimal,Roll No:27,Lab:2.2\n");

    return 0;
}
