// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include "./GameOfLife.h"

// Main function.
int main(int argc, char** argv) {
    initializeGame();
    // Check if mouse clicked and get click coordinates.
    bool automatic = 0;
    int iteration = 0;
    while (true) {
        MEVENT event;
        int key = getch();
        int input = processUserInput(key);
        if (input == 1) {
            updateState();
            showState();
            iteration++;
        }
        if (input == 27) {
            break;
        }
        if (input == 2) {
            automatic = !automatic;
        }
        if (automatic) {
            updateState();
            showState();
            iteration++;
            usleep(1000 * 500);
        }
        mvprintw(0, 0, "iteration:  %d", iteration);
    }
    // Clean up.
    endwin();
}
