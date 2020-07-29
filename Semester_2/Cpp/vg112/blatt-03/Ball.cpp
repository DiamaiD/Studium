// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include "./Ball.h"

double cx;
double cy;
int rx;
int ry;
double gx;
double gy;

// ___________________________________________________________________________
void initTerminal() {
    initscr();              // Initializiation.
    cbreak();               // Don't wait for RETURN.
    noecho();               // Don't echo key presses on screen.
    curs_set(false);        // Don't show the cursor.
    nodelay(stdscr, true);  // Don't wait until key pressed.
    keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.

    cx = COLS / 2.0;
    cy = LINES / 2.0;
    rx = 10;
    ry = 5;
    gx = 0.0;
    gy = 0.0;
}

// ___________________________________________________________________________
void drawBall(bool inverse) {
    if (inverse == true) {
        attron(A_REVERSE);
    } else {
        attroff(A_REVERSE);
    }
    for (int dx = -rx; dx <= +rx; dx++) {
        for (int dy = -ry; dy <= +ry; dy++) {
            if (dx * dx * ry * ry + dy * dy * rx * rx < rx * rx * ry * ry) {
            mvprintw(cy + dy, cx + dx, " ");
            }
        }
    }
}

// ___________________________________________________________________________
int moveBall(int key) {
    if (key == 27) {
        return false;
    }
    switch (key) {
        case KEY_UP:        gy -= 0.0002;   break;
        case KEY_DOWN:      gy += 0.0002;   break;
        case KEY_LEFT:      gx -= 0.0004;   break;
        case KEY_RIGHT:     gx += 0.0004;   break;
    }
    if (cx < 0 || cx > COLS) {
        gx = -gx;
    }
    if (cy < 0 || cy > LINES) {
        gy = -gy;
    }
    cx += gx;
    cy += gy;
    return true;
}
