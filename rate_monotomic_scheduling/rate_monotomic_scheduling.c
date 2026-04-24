#include<stdio.h>
#include<math.h>
int main() {
    int n,i,j,time,limit;
    printf("Enter number of tasks: ");
    scanf("%d",&n);
    int C[10],T[10];
    int remaining[10], next_arrival[10];
    for(i=0;i<n;i++) {
        printf("enter execution time(C) for T%d: ",i+1);
        scanf("%d",&C[i]);
        printf("Enter period(T) for T%d: ",i+1);
        scanf("%d",&T[i]);
        remaining[i] = 0;
        next_arrival[i] = 0;
    }
    float U = 0;
    for(i=0;i<n;i++) {
        U += (float)C[i]/T[i];
    }
    printf("\nCPU Utilization U = %.2f\n",U);
    float bound = n*(pow(2,(float)1/n) - 1);
    printf("RMS bound = %.2f\n",bound);
    if (U > bound) {
        printf("Tasks are not scheduling\n");
        return 0;
    }
    else {
        printf("Tasks are scheduling");
    }
    printf("\n Priority (Smaller period -> Highest priority): \n");
    int idx[10];
    for (i=0;i<n;i++) {
        idx[i] = i;
    }
    for (i=0;i<n;i++) {
        for (j=i+1;j<n;j++) {
            if (T[idx[i]] > T[idx[j]]) {
                int temp = idx[i];
                idx[i] = idx[j];
                idx[j] = temp;
            }
        }
    }
    for(i=0;i<n;i++) {
        printf("T%d",idx[i] + 1);
    }
    printf("\n");
    printf("\nExecution Timeline:\n");
    printf("Enter time limit: ");
    scanf("%d",&limit);
    int current = -1, prev = -1, start = 0;
    for (time=0;time<limit;time++) {
        for (i=0;i<n;i++) {
            if (time == next_arrival[i]) {
                remaining[i] = C[i];
                next_arrival[i] += T[i];
            }
        }
        current = -1;
        for (i=0;i<n;i++) {
            if (remaining[i] > 0) {
                if (current == -1 || T[i] < T[current]) {
                    current = i;
                }
            }
        }
        if (current != prev) {
            if (time != 0) {
                if(prev == -1) {
                    printf("%d - %d: Idle\n",start,time);
                }
                else {
                    printf("%d - %d: T%d\n",start,time,prev+1);
                }
            }
            start = time;
            prev = current;
        }
        if (current != -1) {
            remaining[current]--;
        }
    }
    if (prev == -1) {
        printf("%d - %d: Idle\n",start,limit);
    }
    else {
        printf("%d - %d: T%d\n",start,limit,prev+1);
    }
    return 0;
}
