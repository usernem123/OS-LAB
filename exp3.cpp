#include <iostream>
using namespace std;

int main() {
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0, tatavg = 0;

    cout << "\nEnter the number of processes: ";
    cin >> n;

    for (i = 0; i < n; i++) {
        cout << "\nEnter Burst Time for Process " << i + 1 << ": ";
        cin >> bt[i];
    }

    wt[0] = 0;          // Waiting time for the first process
    tat[0] = bt[0];     // Turnaround time for the first process

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Calculate averages
    wtavg = wtavg / n;
    tatavg = tatavg / n;

    // Display results
    cout << "\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (i = 0; i < n; i++) {
        cout << "\n\tP" << i + 1 << "\t\t"
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i];
    }

    cout << "\nAverage Waiting Time: " << wtavg;
    cout << "\nAverage Turnaround Time: " << tatavg << endl;

    return 0;
}
