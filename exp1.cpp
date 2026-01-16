#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        std::cerr << "fork failed" << std::endl;
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        execlp("whoami", "whoami", NULL);
        exit(0);  // exit if execlp fails
    } 
    else {
        // Parent process
        std::cout << "\nProcess ID is: " << getpid() << std::endl;
        wait(NULL);  // Wait for the child process to finish
        exit(0);
    }

    return 0;
}
