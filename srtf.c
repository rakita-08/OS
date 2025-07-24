#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    bool started;
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
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].started = false;
    }

    int completed = 0, current_time = 0;
    int prev = -1;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    // To store process executed at each time unit for Gantt chart
    int gantt[1000]; // assuming max time span
    int gantt_len = 0;

    while (completed < n) {
        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                if (proc[i].remaining_time < min_rt) {
                    min_rt = proc[i].remaining_time;
                    idx = i;
                }
                // If tie, pick process with earlier arrival time
                else if (proc[i].remaining_time == min_rt) {
                    if (proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // CPU idle
            gantt[gantt_len++] = -1;
            current_time++;
            continue;
        }

        if (!proc[idx].started) {
            proc[idx].response_time = current_time - proc[idx].arrival_time;
            proc[idx].started = true;
        }

        // Run process for one unit of time
        proc[idx].remaining_time--;
        gantt[gantt_len++] = proc[idx].pid;
        current_time++;

        if (proc[idx].remaining_time == 0) {
            proc[idx].completion_time = current_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;

            total_wt += proc[idx].waiting_time;
            total_tat += proc[idx].turnaround_time;
            total_rt += proc[idx].response_time;

            completed++;
        }
    }

    // Print process details
    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");

    // Print top bar
    for (int i = 0; i < gantt_len; i++) {
        printf(" ");
        printf("--");
    }
    printf("\n|");

    // Print process IDs or idle for gantt
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

    // Print timeline below chart
    printf("0");
    for (int i = 1; i <= gantt_len; i++) {
        printf("  %d", i);
    }
    printf("\n");
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.5c\n");
    return 0;
}
