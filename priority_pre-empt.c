// PRE-EMPTIVE PRIORITY SCHEDULING ALGORITHM 
//HIGHER PRIORITY GIVEN MORE PREFERENCE.


#include <stdio.h> 

int main() {
    int n;

    printf("Enter no. of process: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], prior[n], done[n],rt[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("\nEnter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &prior[i]);

        done[i] = 0;
        rt[i] = bt[i];          // initiating remaining time as burst time
    }

    int curr_time = 0;       // cpu time
    int completed = 0;

    while (completed < n) {    // till all the process get completed loop runs.

        int idx = -1;
        int high_prior = -1;

        for (int i = 0; i < n; i++) {

            if (at[i] <= curr_time && done[i] == 0) {

                if (prior[i] > high_prior) {
                    high_prior = prior[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {            // cpu idle
            curr_time++;
        }
        else {

            //process executed for unit time
            rt[idx]--;
            curr_time++;

            if(rt[idx] == 0){           // if remaining time is 0, it means process get completed.
                ct[idx] = curr_time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
    
                done[idx] = 1;              // marking as the process get completed.
                completed++;
            }
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], prior[i],
               ct[i], tat[i], wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    total_tat /= n;
    total_wt /= n;

    printf("\nAverage waiting time: %.2f", total_wt);
    printf("\nAverage turn around time: %.2f", total_tat);

    return 0;
}