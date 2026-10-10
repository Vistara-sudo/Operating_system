//========================== SJF -->> Shortest Job First algorithm===========================

// --------------------MAIN DRAWBACKS OF THIS SJF CODE--------------------
// O(n^2) time complexity due to repeated process scanning
// Equal burst times are handled by input order
// Variable length array.
// INEFFICIENT CPU TIME HANDLING
// GANTT CHART DISPLAY

#include<stdio.h>
#include<limits.h>

int main(){
    int n;
    printf("Enter the no. of process: ");
    scanf("%d",&n);

    int at[n],bt[n],ct[n],tat[n],wt[n],done[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        // done[i] prevents the CPU from selecting a process that has already finished.
        done[i] = 0;        // If 0-->> means process not completed  1-->> means process finished
    }

    int current_time =0;        // cpu time
    int completed =0;

    while(completed<n){
       int idx = -1;
       int min_bt = INT_MAX;
       for(int i=0;i<n;i++){
            if(at[i]<= current_time && done [i] == 0){          //Select arrived and unfinished process
                if(min_bt > bt[i]){
                    min_bt = bt[i];
                    idx = i;
                }
            }
       }

       if(idx == -1){
            current_time++;
            continue;
       }

       current_time += bt[idx];
       ct[idx] = current_time;
       tat[idx] = ct[idx] - at[idx];
       wt[idx] = tat[idx] - bt[idx];

       done[idx] = 1;
       completed++;
    }

    float avg_tat=0,avg_wt=0;

    printf("\t\t\t\t\033[1;32mCALCULATION TABLE\033[0m\n");

    printf("\nP-id\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\n\nAverage Turn Around Time: %.2f",avg_tat/n);
    printf("\nAverage Wating Time: %.2f",avg_wt/n);
    return 0;
}