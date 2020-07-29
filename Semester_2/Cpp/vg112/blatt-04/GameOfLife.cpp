// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include "./GameOfLife.h"

bool current[200][200] = { 0 };
bool (*pointerCurrent)[200];
bool previous[200][200] = { 0 };
bool (*pointerPrevious)[200];

// ___________________________________________________________________________
void initializeGame() {
    // Initialize.
    initscr();              // Initializiation.
    cbreak();               // Don't wait for RETURN.
    noecho();               // Don't echo key presses on screen.
    curs_set(false);        // Don't show the cursor.
    nodelay(stdscr, true);  // Don't wait until key pressed.
    keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.
    mousemask(ALL_MOUSE_EVENTS, NULL);

    pointerCurrent = current;
    pointerPrevious = previous;
}

// ___________________________________________________________________________
void showState() {
    for (int x = 0; x < MAX; x++) {
        for (int y = 0; y < MAX; y++) {
            if (pointerCurrent[y][x]) {
                attron(A_REVERSE);
                mvprintw(y, x, " ");
            } else {
                attroff(A_REVERSE);
                mvprintw(y, x, " ");
            }
        }
    }
    refresh();
}

// ___________________________________________________________________________
void updateState() {
    bool (*tempPointer)[200] = pointerPrevious;
    pointerPrevious = pointerCurrent;
    pointerCurrent = tempPointer;

    for (int x = 0; x < MAX; x++) {
        for (int y = 0; y < MAX; y++) {
            int alive = aliveNeighbors(x, y);
            pointerCurrent[y][x] = 0;
            if (pointerPrevious[y][x] == 0 && alive == 3) {
                pointerCurrent[y][x] = 1;
            } else if (pointerPrevious[y][x] == 1 &&
            (alive == 2 || alive == 3)) {
                pointerCurrent[y][x] = 1;
            } else if (pointerPrevious[y][x] == 1 && alive > 3) {
                pointerCurrent[y][x] = 0;
            }
        }
    }
}

// ___________________________________________________________________________
int processUserInput(int key) {
    if (key == 27) {
        return 27;
    }
    if (key == 115) {
        return 1;
    }
    if (key == 32) {
        return 2;
    }
    MEVENT event;
    if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
            int x = event.x;  // x-coordinate of click (col index)
            int y = event.y;  // y-coordinate of click (row index)
            pointerCurrent[y][x] = !pointerCurrent[y][x];
            if (pointerCurrent[y][x]) { attron(A_REVERSE); }
            mvprintw(y, x, " ");
            attroff(A_REVERSE);
            refresh();
        }
    }
    return 0;
}

// ___________________________________________________________________________
int aliveNeighbors(int x, int y) {
    int alive = 0;
    if (pointerPrevious[y][(MAX+x+1) % MAX]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y+1) % MAX][(MAX+x+1) % MAX]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y+1) % MAX][x]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y+1) % MAX][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (pointerPrevious[y][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y-1) % MAX][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y-1) % MAX][x]) {
        alive++;
    }
    if (pointerPrevious[(MAX+y-1) % MAX][(MAX+x+1) % MAX]) {
        alive++;
    }
    return alive;
}
