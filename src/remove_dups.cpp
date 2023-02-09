#include "remove_dups.h"
#include <iostream>

int main() {
    std::cout << "Enter string to remove duplicates:" << std::endl;

    std::string str;
    std::getline(std::cin, str);
    remove_dups(str);

    std::cout << "Result: " << str << std::endl;
    return 0;
}
