// NON PRE-EMPTIVE PRIORITY SCHEDULING ALGORITHM 
//HIGHER PRIORITY GIVEN MORE PREFERENCE.

#include <stdio.h> 

int main() {
    int n;

    printf("Enter no. of process: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], prior[n], done[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("\nEnter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &prior[i]);

        done[i] = 0;
    }

    int curr_time = 0;       // cpu time
    int completed = 0;         //no. of process completed

    while (completed < n) {

        int idx = -1;
        int high_prior = -1;

        for (int i = 0; i < n; i++) {

            if (at[i] <= curr_time && done[i] == 0) {

                if (prior[i] > high_prior) {
                    high_prior = prior[i];
                    idx = i;                    //capturing the index of process whose priority is higher
                }
            }
        }

        if (idx == -1) {            // no process has arrived yet.
            curr_time++;
        }
        else {
            curr_time += bt[idx];           // Adding current time + burst time = completion time 

            ct[idx] = curr_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            done[idx] = 1;              // Marking as the process get done..
            completed++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], prior[i],
               ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage waiting time: %.2f", avg_wt);
    printf("\nAverage turn around time: %.2f", avg_tat);

    return 0;
}