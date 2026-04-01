
#include <iostream>
#include "/Users/user/Desktop/linux-25-26/hmw14/util/threadPool.h"

int square(int x) {
    return x * x;
}

int main() {
    ThreadPool pool;

    auto f1 = pool.enqueue(square, 5);
    auto f2 = pool.enqueue([](int a, int b) {
        return a + b;
    }, 3, 4);

    std::cout << "square(5) = " << f1.get() << std::endl;
    std::cout << "3 + 4 = " << f2.get() << std::endl;

    return 0;
}