#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int finished;
} Process;

int main() {
    int n, completed = 0, current_time = 0, min_idx;
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
        proc[i].finished = 0;
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");

    while (completed < n) {
        int min_bt = 1e9;
        min_idx = -1;

        // Find shortest burst time process among arrived and unfinished
        for (int i = 0; i < n; i++) {
            if (!proc[i].finished && proc[i].arrival_time <= current_time) {
                if (proc[i].burst_time < min_bt) {
                    min_bt = proc[i].burst_time;
                    min_idx = i;
                } else if (proc[i].burst_time == min_bt) {
                    // Tie breaker: FCFS
                    if (proc[i].arrival_time < proc[min_idx].arrival_time) {
                        min_idx = i;
                    }
                }
            }
        }

        if (min_idx == -1) {
            current_time++;  // No process ready, CPU idle
            continue;
        }

        proc[min_idx].waiting_time = current_time - proc[min_idx].arrival_time;
        current_time += proc[min_idx].burst_time;
        proc[min_idx].completion_time = current_time;
        proc[min_idx].turnaround_time = proc[min_idx].completion_time - proc[min_idx].arrival_time;
        proc[min_idx].finished = 1;
        completed++;

        total_wt += proc[min_idx].waiting_time;
        total_tat += proc[min_idx].turnaround_time;

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               proc[min_idx].pid,
               proc[min_idx].arrival_time,
               proc[min_idx].burst_time,
               proc[min_idx].completion_time,
               proc[min_idx].waiting_time,
               proc[min_idx].turnaround_time);
    }

    // Print averages
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n|");

    // We print the processes in order of execution by their start time to visualize the chart correctly

    // Create an array to store start times for sorting displayed order
    int start_times[n];
    for (int i = 0; i < n; i++) {
        start_times[i] = proc[i].completion_time - proc[i].burst_time;
    }

    // Sort the processes according to start time for Gantt chart printing
    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i -1; j++) {
            if (start_times[j] > start_times[j+1]) {
                // swap
                int temp_start = start_times[j];
                start_times[j] = start_times[j+1];
                start_times[j+1] = temp_start;

                Process temp_proc = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp_proc;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf(" P%d |", proc[i].pid);
    }
    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n");

    // Print timeline below the Gantt chart
    printf("%d", proc[0].completion_time - proc[0].burst_time);  // start time of first process
    for (int i = 0; i < n; i++) {
        printf("   %d", proc[i].completion_time);
    }
    printf("\n");
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.5b\n");
    return 0;
}
