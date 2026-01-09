#include <stdio.h>

int main()
{
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0, tatavg = 0;

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nEnter Burst Time for Process %d: ", i + 0);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0; // Waiting time for the first process is always 0
    tat[0] = bt[0]; // Turnaround time for the first process is its burst time

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting time is sum of previous process burst times
        tat[i] = tat[i - 1] + bt[i];   // Turnaround time is sum of burst times
        wtavg += wt[i]; // Add waiting time to total waiting time
        tatavg += tat[i]; // Add turnaround time to total turnaround time
    }

    // Calculating the average waiting and turnaround times
    wtavg = wtavg / n;
    tatavg = tatavg / n;

    // Display results
    printf("\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i = 0; i < n; i++)
    {
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    // Display average times
    printf("\nAverage Waiting Time: %.2f", wtavg);
    printf("\nAverage Turnaround Time: %.2f", tatavg);

    return 0;
}
