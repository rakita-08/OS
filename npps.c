#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int started;  // flag to check if process is completed
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for process %d (lower value = higher priority): ", i + 1);
        scanf("%d", &proc[i].priority);
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].completion_time = 0;
        proc[i].started = 0;
    }

    int completed = 0;
    int current_time = 0;
    int prev_process = -1;

    float total_wt = 0, total_tat = 0;

    printf("\nScheduling order (process ids): ");

    while (completed < n) {
        int idx = -1;
        int highest_priority = 1e9;

        // Find highest priority process that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!proc[i].started && proc[i].arrival_time <= current_time) {
                if (proc[i].priority < highest_priority) {
                    highest_priority = proc[i].priority;
                    idx = i;
                } else if (proc[i].priority == highest_priority) {
                    // If same priority, choose earliest arrival
                    if (proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // No process arrived yet, increment time
            current_time++;
            continue;
        }

        // Schedule selected process
        proc[idx].started = 1;
        if (prev_process != idx) {
            printf("P%d ", proc[idx].pid);
            prev_process = idx;
        }
        proc[idx].waiting_time = current_time - proc[idx].arrival_time;
        proc[idx].completion_time = current_time + proc[idx].burst_time;
        proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;

        current_time += proc[idx].burst_time;
        completed++;

        total_wt += proc[idx].waiting_time;
        total_tat += proc[idx].turnaround_time;
    }

    printf("\n\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    // Gantt Chart Display
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < proc[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Printing process IDs in execution order (sorted by completion time)
    // We need to order processes by start time for Gantt chart

    // Create an array to store start time and an index array to order processes
    int start_times[n];
    int indices[n];
    for (int i = 0; i < n; i++) {
        start_times[i] = proc[i].completion_time - proc[i].burst_time;
        indices[i] = i;
    }

    // Simple bubble sort by start_times
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (start_times[j] > start_times[j+1]) {
                int temp = start_times[j];
                start_times[j] = start_times[j+1];
                start_times[j+1] = temp;
                int temp_i = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp_i;
            }
        }
    }

    // Print processes in order
    for (int i = 0; i < n; i++) {
        int btime = proc[indices[i]].burst_time;
        for (int j = 0; j < btime - 1; j++) printf(" ");
        printf("P%d", proc[indices[i]].pid);
        for (int j = 0; j < btime - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf(" ");
        for (int j = 0; j < proc[indices[i]].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // Print time line starting from 0
    printf("0");
    for (int i = 0; i < n; i++) {
        int end_time = proc[indices[i]].completion_time;
        for (int j = 0; j < proc[indices[i]].burst_time; j++) printf("  ");
        printf("%d", end_time);
    }
    printf("\n");
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.5e\n");
    return 0;
}
