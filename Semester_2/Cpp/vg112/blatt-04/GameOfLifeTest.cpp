// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./GameOfLife.h"

TEST(GameOfLifeTest, GameOfLife) {
    pointerCurrent = current;
    pointerPrevious = previous;
    ASSERT_EQ(0, pointerCurrent[0][0]);
    ASSERT_EQ(0, aliveNeighbors(1, 1));
    pointerCurrent[0][0] = 1;
    pointerCurrent[0][1] = 1;
    pointerCurrent[1][0] = 1;
    updateState();
    ASSERT_EQ(1, pointerCurrent[1][1]);
    ASSERT_EQ(3, aliveNeighbors(1, 1));
    ASSERT_EQ(0, aliveNeighbors(51, 101));
}
