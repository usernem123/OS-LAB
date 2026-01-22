#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int numprocess = 1;

    pid_t pid1 = fork();

    if (pid1 < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }
    else if (pid1 == 0) {
        // -------- Child 1 --------
        numprocess++;

        pid_t pid2 = fork();

        if (pid2 < 0) {
            cerr << "Fork failed" << endl;
            return 1;
        }
        else if (pid2 == 0) {
            // -------- Child 2 (LAST created, prints FIRST) --------
            numprocess++;
            cout << "Process " << numprocess
                 << " (LAST created): PID = " << getpid() << endl;
        }
        else {
            // Child 1 waits for Child 2
            wait(NULL);
            cout << "Process " << numprocess
                 << ": PID = " << getpid() << endl;
        }
    }
    else {
        // -------- Parent process --------
        wait(NULL);  // Wait for Child 1
        cout << "Process " << numprocess
             << " (FIRST created): PID = " << getpid() << endl;
    }

    return 0;
}
