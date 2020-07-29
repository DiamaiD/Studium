// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <ncurses.h>
#include "./GameOfLife.h"


int GameOfLife::_numObjects = 0;

// ____________________________________________________________________________
GameOfLife::GameOfLife(bool ncurses) {
    _ncurses = ncurses;
    _numObjects++;
    _objectId = _numObjects;
}

// ____________________________________________________________________________
GameOfLife::~GameOfLife() {
    endwin();
}

// ___________________________________________________________________________
void GameOfLife::initializeGame() {
    // Initialize.
    if (_ncurses) {
        initscr();              // Initializiation.
        cbreak();               // Don't wait for RETURN.
        noecho();               // Don't echo key presses on screen.
        curs_set(false);        // Don't show the cursor.
        nodelay(stdscr, true);  // Don't wait until key pressed.
        keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.
        mousemask(ALL_MOUSE_EVENTS, NULL);
    }

    _cellsAlive = 0;
    _automatic = 0;
    _iteration = 0;

    _current[MAX][MAX] = { 0 };
    _previous[MAX][MAX] = { 0 };

    _pointerCurrent = _current;
    _pointerPrevious = _previous;
}

// ___________________________________________________________________________
void GameOfLife::showState() {
    for (int x = 0; x < MAX; x++) {
        for (int y = 0; y < MAX; y++) {
            if (_pointerCurrent[y][x]) {
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
void GameOfLife::updateState() {
    bool (*tempPointer)[MAX] = _pointerPrevious;
    _pointerPrevious = _pointerCurrent;
    _pointerCurrent = tempPointer;

    _cellsAlive = 0;

    for (int x = 0; x < MAX; x++) {
        for (int y = 0; y < MAX; y++) {
            int alive = aliveNeighbors(x, y);
            _pointerCurrent[y][x] = 0;
            if (_pointerPrevious[y][x] == 0 && alive == 3) {
                _pointerCurrent[y][x] = 1;
                _cellsAlive++;
            } else if (_pointerPrevious[y][x] == 1 &&
            (alive == 2 || alive == 3)) {
                _pointerCurrent[y][x] = 1;
                _cellsAlive++;
            } else if (_pointerPrevious[y][x] == 1 && alive > 3) {
                _pointerCurrent[y][x] = 0;
            }
        }
    }
}

// ___________________________________________________________________________
int GameOfLife::processUserInput(int key, MEVENT event) {
    if (key == 27) {
        return 27;
    }
    if (key == 115) {
        return 1;
    }
    if (key == 32) {
        return 2;
    }
    if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
            _x = event.x;  // x-coordinate of click (col index)
            _y = event.y;  // y-coordinate of click (row index)
            _pointerCurrent[_y][_x] = !_pointerCurrent[_y][_x];
            if (_pointerCurrent[_y][_x]) {
                _cellsAlive++;
                attron(A_REVERSE);
            } else {
                _cellsAlive--;
            }
            mvprintw(_y, _x, " ");
            attroff(A_REVERSE);
            refresh();
        }
    }
    return 0;
}

// ___________________________________________________________________________
int GameOfLife::aliveNeighbors(int x, int y) {
    int alive = 0;
    if (_pointerPrevious[y][(MAX+x+1) % MAX]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y+1) % MAX][(MAX+x+1) % MAX]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y+1) % MAX][x]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y+1) % MAX][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (_pointerPrevious[y][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y-1) % MAX][(MAX+x-1) % MAX]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y-1) % MAX][x]) {
        alive++;
    }
    if (_pointerPrevious[(MAX+y-1) % MAX][(MAX+x+1) % MAX]) {
        alive++;
    }
    return alive;
}

void GameOfLife::play() {
    while (true) {
        MEVENT event;
        int key = getch();
        int input = processUserInput(key, event);
        if (input == 1) {
            updateState();
            showState();
            _iteration++;
        }
        if (input == 27) {
            break;
        }
        if (input == 2) {
            _automatic = !_automatic;
        }
        if (_automatic) {
            updateState();
            showState();
            _iteration++;
            usleep(1000 * 500);
        }
        mvprintw(0, 0, "iteration:  %d      cells alive:  %d"
        , _iteration, _cellsAlive);
    }
}
