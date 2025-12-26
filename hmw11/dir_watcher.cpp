#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;

    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv[1],
                               IN_CREATE | IN_DELETE | IN_MODIFY | IN_ACCESS);

    char buf[4096];

    while (true) {
        int len = read(fd, buf, sizeof(buf));
        int i = 0;

        while (i < len) {
            auto* e = (inotify_event*)(buf + i);
            std::cout << "changed\n";
            i += sizeof(inotify_event) + e->len;
        }
    }
}