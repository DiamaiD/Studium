// Copyright 2020, Viktor Gange
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include "./ApproximateEulersNumber.h"

// Check the ApproximateEulersNumber function with a few examples
TEST(ApproximateEulersNumberTest, approximateEulersNumber) {
    ASSERT_FLOAT_EQ(1.0, approximateEulersNumber(0));
    ASSERT_FLOAT_EQ(2.0, approximateEulersNumber(1));
    ASSERT_FLOAT_EQ(2.718282, approximateEulersNumber(10));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
