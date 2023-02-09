#include "num_to_bits.h"
#include <gtest/gtest.h>

template<typename T>
std::string convert_num_to_bits_lib(T num) {
    return std::bitset<8 * sizeof(T)>(num).to_string();
}

class num_to_bits_fixture : public ::testing::TestWithParam<int> {
};

TEST_P(num_to_bits_fixture, conversion) {
    auto expected = convert_num_to_bits_lib(GetParam());
    ASSERT_EQ(expected, convert_num_to_bits(GetParam()));
}

std::string test_name_generator(const ::testing::TestParamInfo<num_to_bits_fixture::ParamType> &info) {
    return std::to_string(abs((int64_t) info.param));
}

INSTANTIATE_TEST_SUITE_P(
        zero,
        num_to_bits_fixture,
        ::testing::Values(0),
        test_name_generator);

INSTANTIATE_TEST_SUITE_P(
        positive,
        num_to_bits_fixture,
        ::testing::Values(1, 7, 8, 255, 256, 1000, 1234567, INT_MAX),
        test_name_generator);

INSTANTIATE_TEST_SUITE_P(
        negative,
        num_to_bits_fixture,
        ::testing::Values(-1, -7, -8, -254, -255, -256, -1000, -1234567, INT_MIN),
        test_name_generator);

