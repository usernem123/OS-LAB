#include <iostream>
#include <vector>
using namespace std;

#define MAX 10

int main() {
    int n, tq;
    vector<int> at(MAX), bt(MAX), rem_bt(MAX);
    vector<int> ct(MAX), tat(MAX), wt(MAX);
    int time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nProcess P" << i + 1 << endl;
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        rem_bt[i] = bt[i];
    }

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    while (completed < n) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                done = false;

                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }

        if (done)
            time++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];

        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "\nAverage Turnaround Time = " << avg_tat / n << endl;
    cout << "Average Waiting Time = " << avg_wt / n << endl;

    return 0;
}
