#include "remove_dups.h"
#include <string>
#include <gtest/gtest.h>

using namespace std::string_literals;

TEST(remove_dups, empty_string) {
    std::string test = ""s;
    remove_dups(test);
    ASSERT_EQ(""s, test);
}

TEST(remove_dups, only_dups) {
    std::string test = "11111111111"s;
    remove_dups(test);
    ASSERT_EQ("1"s, test);
}

TEST(remove_dups, no_dups) {
    std::string test = "qwertyuiop"s;
    remove_dups(test);
    ASSERT_EQ("qwertyuiop"s, test);
}

TEST(remove_dups, complex_dups) {
    std::string test = "iiiii aaaammmm    ddddduuuuplicatttteeeeddd"s;
    remove_dups(test);
    ASSERT_EQ("i am duplicated"s, test);
}