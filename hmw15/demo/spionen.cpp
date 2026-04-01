
#include <iostream>
#include <csignal>
#include <unistd.h>

void handler(int sig) {
    if (sig == SIGUSR1) {
        std::cout << "Spion received SIGUSR1, sending SIGUSR2\n";
        kill(getppid(), SIGUSR2); // reply to parent
    }
}

int main() {
    signal(SIGUSR1, handler);

    std::cout << "Spion PID: " << getpid() << std::endl;

    while (true) {
        pause(); // wait for signals
    }

    return 0;
}