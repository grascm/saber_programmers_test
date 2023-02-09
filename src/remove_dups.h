#pragma once

#include <string>

void remove_dups(std::string& str)
{
    if (str.size() < 2) return;

    char cur_char = str[0];
    std::size_t next_pos = 1;

    for (std::size_t i = next_pos; i < str.size(); i++)
    {
        if (cur_char == str[i]) continue;

        str[next_pos++] = str[i];
        cur_char = str[i];
    }
    str.erase(str.begin() + next_pos, str.end());
}