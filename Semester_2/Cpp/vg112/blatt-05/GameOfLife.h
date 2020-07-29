// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <gtest/gtest.h>

// Class for the Game called GameOfLife
class GameOfLife {
 public:
    // Create an instance of the Object GameOfLife
    explicit GameOfLife(bool ncurses);

    // Prepare the terminal and the Object.
    void initializeGame();

    // Play the GameOfLife
    void play();

    // Destructor which says goodbye.
    ~GameOfLife();

 private:
    bool _ncurses;
    static const int MAX = 200;
    bool _current[MAX][MAX];
    bool _previous[MAX][MAX];
    bool (*_pointerCurrent)[MAX];
    bool (*_pointerPrevious)[MAX];

    int _x;
    int _y;

    int _cellsAlive;

    bool _automatic;
    int _iteration;

    // Counter for the number of objects created.
    static int _numObjects;
    // Index of this object.
    int _objectId;

    // Draw the current state of the Game.
    void showState();

    // Check how many neighbors are alive from the current coordinates.
    int aliveNeighbors(int x, int y);

    // Perfrom one GameOfLife step.
    void updateState();

    // Get input from user and react to it.
    int processUserInput(int key, MEVENT event);

    FRIEND_TEST(GameOfLifeTest, initializeGame);
};

#endif  // GAMEOFLIFE_H_
