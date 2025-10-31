
#include <iostream>
#include <vector>
#include </Users/user/Desktop/linux-25-26/iterators/iters/circular_int_iterator.h>

int main() {
    std::vector<int> numbers ;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    circular_int_iterator_builder circular(numbers.data(), numbers.size());

    for (int i = 0; i < 7; ++i) {
        std::cout << *circular << " "; // Access the current element
        ++circular;// Move to the next element
    }
    // Expected Output: 10 20 30 10 20 30 10

    return 0;
}

