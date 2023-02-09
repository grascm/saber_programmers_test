#pragma once

#include <string>

template <typename Int>
std::string convert_num_to_bits(Int num)
{
    auto string_size = sizeof(num) * 8;
    std::string res(string_size, '0');

    std::function<char(Int num)> get_next_bit = [](Int num) { return (num % 2) == 0 ? '0' : '1'; };
    if (num < 0)
    {
        num++;
        get_next_bit = [](Int num) { return (num % 2) == 0 ? '1' : '0'; };
    }

    int64_t pos = string_size - 1;
    while(pos >= 0)
    {
        res[pos--] = get_next_bit(num);
        num /= 2;
    }
    return res;
}