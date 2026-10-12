// --------------------MAIN DRAWBACKS OF THIS ROUND ROBIN CODE--------------------
// Processes must  be entered in sorted arrival-time order
// Need to use circular queue due to queue overflow.
// Variable length array.
// INEFFICIENT CPU TIME HANDLING
// No explicit handling of simultaneous arrivals
// GANTT CHART DISPLAY

#include <stdio.h>


int queue[100];
int front = -1;
int rear = -1;
int size = 100;

void enqueue(int val){
    if(rear == size-1 ){
        return;
    }
    if(front == -1){
        front =0;
    }
    queue[++rear] = val;
}

int dequeue(){
    if(front == -1){
        return -1;
    }else{
        int val = queue[front++];

        if(front > rear){
            front = rear = -1;  // Resetting queue when it becomes empty
        }
        return val;
    }
}

int main(){
    int n;
    printf("Enter no. of process: ");
    scanf("%d",&n);

    int at[n],bt[n],ct[n],tat[n],wt[n],rt[n],found[n];
    int tq;

    for(int i =0;i<n;i++){
        printf("Enter arrival time for P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter burst time for P%d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
        found[i]= 0;        // IT SIGNIFY THE PROCESS HAS NOT ENTERED READY QUEUE
    }

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    // TIME QUANTUM VALIDATION
    if(tq <= 0){        
    printf("Time quantum must be greater than zero.\n");
    return 1;
}

    int curr_time =0;
    int completed =0;

    while(completed < n){
        for(int i=0; i<n;i++){
            if(at[i] <= curr_time && found[i] == 0){
                enqueue(i);
                found[i] = 1;       // IT SIGNIFY THE PROCESS HAS ENTERED READY QUEUE ATLEAST ONCE.
            }
        }

        // If no process arrived it means queue is empty.. Increase time
        if(front == -1 || front > rear){
            curr_time++;
            continue;
        }

        int x = dequeue();          // Taking a process out of queue

        if(rt[x]> tq){
            curr_time +=tq;
            rt[x] -= tq;
        }else{
            curr_time +=rt[x];
            rt[x] = 0;
        }
        

        // Entering new process in queue which get arrived during current process execution
        // This scans processes in their input order, not in arrival-time order.
        for(int i=0; i<n;i++){          
            if(at[i] <= curr_time && found[i] == 0){
                enqueue(i);
                found[i] = 1;
            }
        }

        if(rt[x]>0){                // If a new process arrives as the time quantum expires, enqueue it before the preempted process.
            enqueue(x);         
        }

        if(rt[x] == 0){             //Remaining time become 0 means process has completed..
            ct[x] = curr_time;
            tat[x] = ct[x] - at[x];
            wt[x] = tat[x] - bt[x];
            completed++;
        }
    }
    
    float avg_tat=0;
    float avg_wt=0;

    printf("\t\t\t\t\033[1;32mTime Quantum = %ds\033[0m\n",tq);

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