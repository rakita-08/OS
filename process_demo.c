#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("This is the parent process. PID: %d\n", getpid());

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process created. PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child process is running...\n");
        sleep(2);  // Simulate some work
        printf("Child process terminating.\n");
    } else {
        // Parent process
        printf("Parent is waiting for child to terminate...\n");
        wait(NULL);  // Wait for child to finish
        printf("Child terminated. Parent process continuing.\n");
    }

    printf("Process with PID %d is exiting.\n", getpid());
    printf("Name:Rakita Rimal,Roll No:27,Lab:2.1\n");
    return 0;
}
