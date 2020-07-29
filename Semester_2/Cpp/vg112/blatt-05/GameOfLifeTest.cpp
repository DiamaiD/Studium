// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./GameOfLife.h"

TEST(GameOfLifeTest, initializeGame) {
    GameOfLife game(false);
    game.initializeGame();
    ASSERT_EQ(game._pointerCurrent[0][0], false);
    ASSERT_EQ(game.aliveNeighbors(1, 1), false);
    game._pointerCurrent[0][0] = 1;
    game._pointerCurrent[0][1] = 1;
    game._pointerCurrent[1][0] = 1;
    game.updateState();
    ASSERT_EQ(game._cellsAlive, 4);
    ASSERT_EQ(1, game._pointerCurrent[1][1]);
    ASSERT_EQ(3, game.aliveNeighbors(1, 1));
    ASSERT_EQ(0, game.aliveNeighbors(51, 101));
    MEVENT event;
    ASSERT_EQ(game.processUserInput(0, event), 0);
    ASSERT_EQ(game.processUserInput(27, event), 27);
    ASSERT_EQ(game.processUserInput(32, event), 2);
}
