#include "serializer.h"
#include <gtest/gtest.h>

class serializer_fixture : public ::testing::TestWithParam<int> {
};

TEST_P(serializer_fixture, roundtrip) {
    srand(time(NULL));

    RandomDataList list(GetParam());
    auto buffer = list.SerializeToBuffer();

    List deserialized;
    deserialized.DeserializeFromBuffer(buffer);

    ASSERT_EQ(list, deserialized);
}

INSTANTIATE_TEST_SUITE_P(
        different_sizes,
        serializer_fixture,
        ::testing::Values(0, 1, 2, 3, 10, 15, 18, 45),
        [](auto info) {
            return "size_" + std::to_string(info.param);
        });