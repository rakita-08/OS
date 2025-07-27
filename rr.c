#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    int completed = 0, current_time = 0, i;
    int queue[1000]; // increased size for safety
    int front = 0, rear = 0;
    int visited[n];

    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
        visited[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int min_arrival = proc[0].arrival_time;
    for (i = 1; i < n; i++) {
        if (proc[i].arrival_time < min_arrival)
            min_arrival = proc[i].arrival_time;
    }
    current_time = min_arrival;

    for (i = 0; i < n; i++) {
        if (proc[i].arrival_time == current_time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nProcess execution order:\n");

    while (completed < n) {
        if (front == rear) {
            int next_arrival = 1e9;
            for (i = 0; i < n; i++) {
                if (!visited[i] && proc[i].arrival_time < next_arrival)
                    next_arrival = proc[i].arrival_time;
            }
            current_time = next_arrival;
            for (i = 0; i < n; i++) {
                if (!visited[i] && proc[i].arrival_time <= current_time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        int exec_time = (proc[idx].remaining_time > quantum) ? quantum : proc[idx].remaining_time;
        printf("P%d ", proc[idx].pid);

        proc[idx].remaining_time -= exec_time;
        current_time += exec_time;

        for (i = 0; i < n; i++) {
            if (!visited[i] && proc[i].arrival_time <= current_time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (proc[idx].remaining_time > 0) {
            queue[rear++] = idx;
        } else {
            proc[idx].completion_time = current_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            completed++;
        }
    }

    // Display results
    float total_wt = 0, total_tat = 0;
    printf("\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Name: Rakita Rimal, Roll No: 27, Lab No: 2.5d\n");

    return 0;
}
