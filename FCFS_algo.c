// First Come, First Serve
//Need to add sorting if process is not given as input in ascending order of arrival time.

#include<stdio.h>

int main(){
    int n;
    printf("Enter the no. of process: ");
    scanf("%d",&n);
    int at[n],bt[n],ct[n],tat[n],wt[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("\nEnter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    int current_time =0;        // cpu time

        for(int i=0;i<n;i++){
            if(current_time<at[i]){
                current_time = at[i];
            }
                current_time += bt[i];
                ct[i] = current_time;
                tat[i] = ct[i] - at[i];
                wt[i] = tat[i] - bt[i];

        }


    float avg_wt = 0, avg_tat = 0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage waiting time: %.2f", avg_wt);
    printf("\nAverage turn around time: %.2f", avg_tat);




    return 0;
}