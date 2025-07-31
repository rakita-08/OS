#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10  // Max number of processes
#define MAX_R 10  // Max number of resource types

int main() {
    int n, m; // n = number of processes, m = number of resources
    int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int avail[MAX_R];
    bool finish[MAX_P] = {false};
    int safe_seq[MAX_P], index = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    for (int count = 0; count < n; count++) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int r = 0; r < m; r++) {
                    if (need[p][r] > avail[r]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int r = 0; r < m; r++)
                        avail[r] += alloc[p][r];
                    safe_seq[index++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) break; // No process could be allocated in this cycle
    }

    // Check if system is in a safe state
    bool safe = true;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            safe = false;
            break;
        }
    }

    printf("\n=== Result ===\n");
    if (safe) {
        printf("System is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
    } else {
        printf("System is in an UNSAFE state. No safe sequence exists.\n");
    }

    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 2.6a\n");
    return 0;
}
