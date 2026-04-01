#include <iostream>
#include <thread>
#include "/Users/user/Desktop/linux-25-26/hmw13/util/blocking_queue.h"

        BlockingQueue<int> q(5);

void producer() {
    for (int i = 1; i <= 10; ++i) {
        q.push(i);
        std::cout << "Produced: " << i << std::endl;
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        int val = q.pop();
        std::cout << "Consumed: " << val << std::endl;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}