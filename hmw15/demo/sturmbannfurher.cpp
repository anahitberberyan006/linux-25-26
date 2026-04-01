#include <iostream>
#include <vector>
#include <csignal>
#include <unistd.h>
#include <fstream>
#include <sstream>

volatile sig_atomic_t got_response = 0;

void handler(int sig) {
    if (sig == SIGUSR2) {
        got_response = 1;
    }
}

int main() {
    signal(SIGUSR2, handler);

    std::ifstream file("/tmp/reichspost.txt");
    std::vector<int> pids;

    int pid;
    while (file >> pid) {
        pids.push_back(pid);
    }

    for (int p : pids) {
        std::cout << "Checking PID: " << p << std::endl;

        got_response = 0;
        kill(p, SIGUSR1);

        sleep(1); // wait response

        if (got_response) {
            std::cout << "Spion found! PID = " << p << std::endl;

            kill(p, SIGILL); // terminate
            break;
        }
    }

    return 0;
}//
// Created by user on 01.04.26.
//

#include "sturmbannfurher.h"
