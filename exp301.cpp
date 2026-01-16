#include <iostream>
using namespace std;

int main() {
    int p[20], bt[20], wt[20], tat[20];
    int i, k, n, temp;
    float wtavg = 0, tatavg = 0;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (i = 0; i < n; i++) {
        p[i] = i;
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];
    }

    // Sorting processes by Burst Time (SJF)
    for (i = 0; i < n; i++) {
        for (k = i + 1; k < n; k++) {
            if (bt[i] > bt[k]) {
                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;

                temp = p[i];
                p[i] = p[k];
                p[k] = temp;
            }
        }
    }

    // Waiting Time and Turnaround Time Calculation
    wt[0] = 0;
    tat[0] = bt[0];

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
    }

    // Average Calculation
    for (i = 0; i < n; i++) {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t\t"
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time = " << wtavg / n << endl;
    cout << "Average Turnaround Time = " << tatavg / n << endl;

    return 0;
}
