#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 2)
        return 1;

    std::vector<std::string> input;
    std::string word;

    while (std::cin >> word)
        input.push_back(word);

    std::vector<char*> args;

    for (int i = 1; i < argc; ++i)
        args.push_back(argv[i]);

    for (auto& s : input)
        args.push_back(const_cast<char*>(s.c_str()));

    args.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args.data());
        _exit(127);
    }

    if (pid < 0)
        return 1;

    waitpid(pid, nullptr, 0);
    return 0;
}
util/io/process.h

#pragma once

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int do_command(const char* command) {
    if (!command)
        return -1;

    pid_t pid = fork();

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, (char*)nullptr);
        _exit(127);
    }

    if (pid < 0)
        return -1;

    int status;
    waitpid(pid, &status, 0);
    return status;
}