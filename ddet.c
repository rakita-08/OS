#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m; // number of processes and resource types
    int alloc[MAX_P][MAX_R], request[MAX_P][MAX_R], avail[MAX_R];
    bool finish[MAX_P];
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Initialize finish[] array: a process is finished if it has no outstanding requests
    for (i = 0; i < n; i++) {
        finish[i] = false;
    }

    bool progress;
    do {
        progress = false;

        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_finish = true;
                // Check if current process's requests can be satisfied with available resources
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        can_finish = false;
                        break;
                    }
                }
                // If yes, assume it finishes and releases resources
                if (can_finish) {
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    progress = true; // made progress in this iteration
                }
            }
        }
    } while (progress);

    // After no more progress possible, check which processes are unfinished = deadlocked
    bool deadlock = false;
    printf("\n=== Result ===\n");
    for (i = 0; i < n; i++) {
        if (!finish[i]) {
            if (!deadlock) {
                printf("Deadlock detected.\nDeadlocked processes: ");
                deadlock = true;
            }
            printf("P%d ", i);
        }
    }
    if (!deadlock) {
        printf("No deadlock detected. System is in a safe state.\n");
    } else {
        printf("\n");
    }

    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 2.6b\n");
    return 0;
}
