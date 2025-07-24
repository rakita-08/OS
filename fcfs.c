#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

// Sort processes by arrival time
void sortByArrival(Process proc[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    // Input arrival and burst times
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    // Sort by arrival time
    sortByArrival(proc, n);

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time > current_time) {
            current_time = proc[i].arrival_time;  // idle till process arrives
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        current_time += proc[i].burst_time;
        proc[i].completion_time = current_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;

        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    // Print process details
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }

    // Print averages
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");

    // Top bar
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < proc[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process IDs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time - 1; j++) printf(" ");
        printf("P%d", proc[i].pid);
        for (int j = 0; j < proc[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    // Bottom bar
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < proc[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // Timeline with handling idle times
    int time_marker = 0;
    printf("%d", time_marker);
    for (int i = 0; i < n; i++) {
        // Print extra spaces if idle time before process arrives
        if (proc[i].arrival_time > time_marker) {
            for (int j = 0; j < proc[i].arrival_time - time_marker; j++) {
                printf("  ");
            }
            time_marker = proc[i].arrival_time;
            printf("%d", time_marker);
        }
        // Print spaces during burst
        for (int j = 0; j < proc[i].burst_time; j++) {
            printf("  ");
        }
        time_marker += proc[i].burst_time;
        printf("%d", time_marker);
    }
    printf("\n");
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.5a\n");
    return 0;
}
