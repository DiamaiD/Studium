// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include "./Ball.h"

// Draw a ball on the console using ncurses.
int main(int argc, char** argv) {
    initTerminal();
    while (true) {
        int key = getch();
        drawBall(false);
        if (moveBall(key) == false) {
            break;
        }
        drawBall(true);
        refresh();
    }
    endwin();
}
