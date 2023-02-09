#include "num_to_bits.h"
#include <iostream>

int main() {
    std::cout << "Enter number to get it's bit representation:" << std::endl;

    int64_t number;
    std::cin >> number;

    std::cout << "Bits: " << convert_num_to_bits(number) << std::endl;
    return 0;
}
