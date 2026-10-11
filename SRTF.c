//========================== SRTF -->> Shortest Remaining Time First algorithm===========================

// -------------------- MAIN DRAWBACKS OF THIS SRTF CODE --------------------
// 1. Uses variable-length arrays.
// 2. INEFFICIENT CPU TIME HANDLING
// 3. GANTT CHART DISPLAY


#include<stdio.h>
#include<limits.h>

int main(){
    int n;
    printf("Enter the no. of process: ");
    scanf("%d",&n);

    int at[n],bt[n],ct[n],tat[n],wt[n],done[n],rt[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        // done[i] prevents the CPU from selecting a process that has already finished.
        // If 0-->> means process not completed  1-->> means process finished
        done[i] = 0;

        rt[i] = bt[i];
    }

    int current_time =0;        // cpu time
    int completed =0;

    while(completed<n){
       int idx = -1;
       int min_bt = INT_MAX;
       for(int i=0;i<n;i++){
            if(at[i]<= current_time && done [i] == 0){          //Select arrived and unfinished process
                if(min_bt > rt[i]){                         //Comparing process with minimum remaining burst time.
                    min_bt = rt[i];
                    idx = i;
                }
            }
       }

       if(idx == -1){       //CPU Idle time handling
            current_time++;
            continue;
       }

        // -----------------------Improved CPU idle time handling-----------------------
        // if(idx == -1){
        //     int next_arrival = INT_MAX;

        //     for(int i = 0; i < n; i++){
        //         if(done[i] == 0 && at[i] < next_arrival){
        //             next_arrival = at[i];
        //         }
        //     }

        //     current_time = next_arrival;
        //     continue;
        // }


    // Executing process for a unit time...
       rt[idx]--;
       current_time++;

       if(rt[idx] == 0){
           ct[idx] = current_time;
           tat[idx] = ct[idx] - at[idx];
           wt[idx] = tat[idx] - bt[idx];
    
           done[idx] = 1;
           completed++;
       }
    }

    float avg_tat=0,avg_wt=0;

    printf("\t\t\t\t\033[1;32mCALCULATION TABLE OF SRTF\033[0m\n");

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