#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int started; // flag to check if response time recorded
    int start_time; // first execution time
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for process %d (lower number = higher priority): ", proc[i].pid);
        scanf("%d", &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].completion_time = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].started = 0;
        proc[i].start_time = -1;
    }

    int completed = 0;
    int current_time = 0;
    int prev_process = -1;

    // For Gantt chart: store executed process at each time unit (-1 means idle)
    int gantt[1000];
    int gantt_len = 0;

    while (completed < n) {
        // Find process with highest priority (lowest priority value) among arrived and remaining
        int idx = -1;
        int highest_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                if (proc[i].priority < highest_priority) {
                    highest_priority = proc[i].priority;
                    idx = i;
                }
                else if (proc[i].priority == highest_priority) {
                    // Tie breaker: earlier arrival time
                    if (proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // No process available, CPU idle for 1 unit
            gantt[gantt_len++] = -1;
            current_time++;
            continue;
        }

        // If first time running, record start time
        if (proc[idx].started == 0) {
            proc[idx].start_time = current_time;
            proc[idx].started = 1;
        }

        // Run process for 1 time unit (preemptive)
        proc[idx].remaining_time--;
        gantt[gantt_len++] = proc[idx].pid;
        current_time++;

        // If process finished
        if (proc[idx].remaining_time == 0) {
            proc[idx].completion_time = current_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            completed++;
        }
    }

    // Calculate average waiting and turnaround times
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].priority,
               proc[i].completion_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");

    // Print top bar
    for (int i = 0; i < gantt_len; i++) {
        printf(" ");
        printf("--");
    }
    printf("\n|");

    // Print process IDs or idle in Gantt chart
    for (int i = 0; i < gantt_len; i++) {
        if (gantt[i] == -1)
            printf("  ");
        else
            printf("P%d", gantt[i]);
        printf("|");
    }
    printf("\n ");

    // Print bottom bar
    for (int i = 0; i < gantt_len; i++) {
        printf(" ");
        printf("--");
    }
    printf("\n");

    // Print timeline
    printf("0");
    for (int i = 1; i <= gantt_len; i++) {
        printf("  %d", i);
    }
    printf("\n");
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.5f\n");
    return 0;
}
