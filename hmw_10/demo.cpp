#include <cstring>
#include <iostream>
#include "util.h"

struct Data {
    int a;
    double b;
};

int main() {
    Data x ={7, 2.5};

    io::serialize(x, "data.bin");
    Data y = io::deserialize<Data>("data.bin");

    std::cout << (std::memcmp(&x, &y, sizeof(Data)) == 0) << "\n";
}