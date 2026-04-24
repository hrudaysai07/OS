#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
    int n,i;
    int tickets[10],totaltickets = 0;
    int lottery, winner;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for (i=0;i<n;i++)  {
        printf("Enter number of tickets for process P%d: ",i+1);
        scanf("%d",&tickets[i]);
        totaltickets += tickets[i];
    }
    srand(time(0));
    printf("\nTotal tickets = %d\n",totaltickets);
    lottery = rand() % totaltickets + 1;
    printf("Winning ticket number: %d\n",lottery);
    int sum = 0;
    for (i=0;i<n;i++) {
        sum += tickets[i];
        if (lottery <= sum) {
            winner = i + 1;
            break;
        }
    }
    printf("Process P%d wins the lottery and gets the CPU.\n",winner);
    return 0;
}
