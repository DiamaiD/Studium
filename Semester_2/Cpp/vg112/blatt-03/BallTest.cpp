// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./Ball.h"

TEST(BallTest, Ball) {
    ASSERT_FALSE(moveBall(27));
    moveBall(KEY_DOWN);
    ASSERT_FLOAT_EQ(0.0002, gy);
    moveBall(KEY_LEFT);
    ASSERT_FLOAT_EQ(-0.0004, gx);
    gx = 0;
    cx = 0;
    moveBall(KEY_LEFT);
    moveBall(KEY_LEFT);
    ASSERT_FLOAT_EQ(0.0008, gx);
    gy = 0;
    cy = 0;
    moveBall(KEY_UP);
    moveBall(KEY_UP);
    ASSERT_FLOAT_EQ(0.0004, gy);
}
