// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include "./GameOfLife.h"

// Main function.
int main(int argc, char** argv) {
    GameOfLife game(true);
    game.initializeGame();
    game.play();
}
