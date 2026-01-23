#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/* ===== PROCESS STRUCTURE ===== */
struct process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tt;  // Turnaround Time
    int wt;  // Waiting Time
};

/* ===== RECOMMENDED TIME QUANTUM ===== */
float getRecommendedTQ(vector<int> burstTimes) {
    int sum = 0;
    for (int i = 0; i < burstTimes.size(); i++) {
        sum += burstTimes[i];
    }
    return sum / (float)burstTimes.size();
}

/* ===== TABLE DESIGN ===== */
void printTable(string name, vector<process> procs) {
    cout << "\n" << name << endl;
    cout << "+-----+----+----+----+----+----+\n";
    cout << "| PID | AT | BT | CT | TT | WT |\n";
    cout << "+-----+----+----+----+----+----+\n";

    float sumTT = 0, sumWT = 0;

    for (int i = 0; i < procs.size(); i++) {
        cout << "| " << setw(3) << procs[i].pid
             << " | " << setw(2) << procs[i].at
             << " | " << setw(2) << procs[i].bt
             << " | " << setw(2) << procs[i].ct
             << " | " << setw(2) << procs[i].tt
             << " | " << setw(2) << procs[i].wt << " |\n";

        sumTT += procs[i].tt;
        sumWT += procs[i].wt;
    }

    cout << "+-----+----+----+----+----+----+\n";
    cout << "AVERAGE TURNAROUND TIME : " 
         << fixed << setprecision(2) << sumTT / procs.size() << endl;
    cout << "AVERAGE WAITING TIME    : " 
         << fixed << setprecision(2) << sumWT / procs.size() << endl;
}

/* ===== ROUND ROBIN ===== */
void roundRobin(vector<process> procs, int tq) {
    int n = procs.size();
    vector<int> remaining(n);

    for (int i = 0; i < n; i++)
        remaining[i] = procs[i].bt;

    int time = 0, completed = 0, idx = 0;

    while (completed < n) {
        while (idx < n && remaining[idx] == 0)
            idx++;

        if (idx >= n) {
            idx = 0;
            continue;
        }

        if (remaining[idx] <= tq) {
            time += remaining[idx];
            remaining[idx] = 0;
            completed++;
        } else {
            time += tq;
            remaining[idx] -= tq;
        }

        procs[idx].ct = time;
        idx++;
    }

    for (int i = 0; i < n; i++) {
        procs[i].tt = procs[i].ct - procs[i].at;
        procs[i].wt = procs[i].tt - procs[i].bt;
    }

    printTable("ROUND ROBIN", procs);
}

/* ===== SHORTEST JOB FIRST ===== */
void shortestJobFirst(vector<process> procs) {
    int n = procs.size();
    vector<bool> done(n, false);
    int time = 0;

    for (int c = 0; c < n; c++) {
        int idx = -1, minBT = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && procs[i].at <= time && procs[i].bt < minBT) {
                minBT = procs[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            c--;
            continue;
        }

        time += procs[idx].bt;
        procs[idx].ct = time;
        procs[idx].tt = procs[idx].ct - procs[idx].at;
        procs[idx].wt = procs[idx].tt - procs[idx].bt;
        done[idx] = true;
    }

    printTable("SHORTEST JOB FIRST (SJF)", procs);
}

/* ===== SHORTEST REMAINING TIME FIRST ===== */
void shortestRemainingTimeFirst(vector<process> procs) {
    int n = procs.size();
    vector<int> remaining(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++)
        remaining[i] = procs[i].bt;

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minRT = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && procs[i].at <= time && remaining[i] < minRT) {
                minRT = remaining[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            procs[idx].ct = time;
            procs[idx].tt = procs[idx].ct - procs[idx].at;
            procs[idx].wt = procs[idx].tt - procs[idx].bt;
            done[idx] = true;
            completed++;
        }
    }

    printTable("SHORTEST REMAINING TIME FIRST (SRTF)", procs);
}

/* ===== MAIN ===== */
int main() {
    vector<int> arrivalTimes = {4, 2, 3, 6, 1, 5, 8, 7};
    vector<int> burstTimes   = {53, 43, 18, 16, 44, 73, 99, 27};

    vector<process> processes;

    for (int i = 0; i < arrivalTimes.size(); i++) {
        process p;
        p.pid = i + 1;
        p.at = arrivalTimes[i];
        p.bt = burstTimes[i];
        p.ct = p.tt = p.wt = 0;
        processes.push_back(p);
    }

    float tq = getRecommendedTQ(burstTimes);

    cout << "\nRECOMMENDED TIME QUANTUM: "
         << fixed << setprecision(2) << tq << endl;

    roundRobin(processes, (int)tq);
    shortestJobFirst(processes);
    shortestRemainingTimeFirst(processes);

    return 0;
}
