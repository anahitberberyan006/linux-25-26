#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::vector<int> fake_pids;

    // generate random fake PIDs
    for (int i = 0; i < 5; ++i) {
        fake_pids.push_back(1000 + rand() % 5000);
    }

    // fork spion
    pid_t spion_pid = fork();

    if (spion_pid == 0) {
        execl("./spion", "spion", nullptr);
    }

    sleep(1);

    // add real spion PID
    fake_pids.push_back(spion_pid);

    // shuffle
    std::random_shuffle(fake_pids.begin(), fake_pids.end());

    // write to file
    std::ofstream file("/tmp/reichspost.txt");
    for (int p : fake_pids) {
        file << p << " ";
    }
    file.close();

    // fork sturmbannfuhrer
    pid_t hunter = fork();

    if (hunter == 0) {
        execl("./sturmbannfuhrer", "sturmbannfuhrer", nullptr);
    }

    wait(nullptr);
    wait(nullptr);

    return 0;
}