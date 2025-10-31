
#include <iostream>
#include <vector>
#include </Users/user/Desktop/linux-25-26/iterators/iters/filter_integer_iterator.h>

bool is_even(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    filter_integer_iterator_builder even_iter(numbers.data(), numbers.size(), is_even);

    for (auto it = even_iter.begin(); it != even_iter.end(); ++it) {
        std::cout << *it << " ";
    }
    // Expected Output: 2 4 6
    return 0;
}