#include <iostream>
#include <vector>
#include <climits> // for INT_MAX

using namespace std;

#define MAX 10

int main() {
    int n;
    vector<int> at(MAX), bt(MAX), pr(MAX);
    vector<int> ct(MAX), tat(MAX), wt(MAX);
    vector<int> completed(MAX, 0);
    int time = 0, done = 0;
    float avg_tat = 0, avg_wt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nProcess P" << i + 1 << endl;
        cout << "Arrival Time: ";
        cin >> at[i];
        cout << "Burst Time: ";
        cin >> bt[i];
        cout << "Priority: ";
        cin >> pr[i];
    }

    while (done < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i] && pr[i] < highestPriority) {
                highestPriority = pr[i];
                idx = i;
            }
        }

        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            completed[idx] = 1;
            done++;
        } else {
            time++;
        }
    }

    cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];

        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "\nAverage Turnaround Time = " << avg_tat / n << endl;
    cout << "Average Waiting Time = " << avg_wt / n << endl;

    return 0;
}
