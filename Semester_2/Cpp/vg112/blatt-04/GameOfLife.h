// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

static int MAX = 200;

extern bool current[200][200];
extern bool (*pointerCurrent)[200];
extern bool previous[200][200];
extern bool (*pointerPrevious)[200];

// Prepare the terminal.
void initializeGame();

// Draw the current state of the Game.
void showState();

// Check how many neighbors are alive from the current coordinates.
int aliveNeighbors(int x, int y);

// Perfrom one GameOfLife step.
void updateState();

// Get input from user and react to it.
int processUserInput(int key);

#endif  // GAMEOFLIFE_H_