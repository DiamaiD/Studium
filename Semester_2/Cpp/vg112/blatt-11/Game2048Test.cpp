// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./Game2048.h"

#define up 259
#define right 261
#define down 258
#define left 260
#define universal 1000

TEST(Game2048, constructor) {
  Game2048 game;
  ASSERT_EQ(0, game._undoStates);
  ASSERT_EQ(0, game._stateCounter);
  ASSERT_EQ(0, game._turn);
  ASSERT_EQ(0, game._score);
}

TEST(Game2048, printUsageAndExit) {
  Game2048 game;
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(game.printUsageAndExit(), "Usage: ./Game2048Main .*");
}

TEST(Game2048, parseCommandLineArguments) {
  Game2048 game;
  int argc = 3;
  char* argv[3] = {
    const_cast<char*>("./Game2048Main"),
    const_cast<char*>("--undo-states"),
    const_cast<char*>("7"),
  };
  game.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(7, game._undoStates);
}

TEST(Game2048, parseCommandLineArgumentsShort) {
  Game2048 game;
  int argc = 3;
  char* argv[3] = {
    const_cast<char*>("./Game2048Main"),
    const_cast<char*>("-u"),
    const_cast<char*>("7"),
  };
  game.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(7, game._undoStates);
}

TEST(Game2048, parseCommandLineWithNoArguments) {
  Game2048 game;
  int argc = 1;
  char* argv[1] = {
    const_cast<char*>("./Game2048Main"),
  };
  game.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(0, game._undoStates);
}

TEST(Game2048, initializeGame) {
  Game2048 game;
  // we dont init ncurses, thats why we have to manually set the
  // terminal parameters which we will need for this function
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  ASSERT_EQ(7, game._tileSize);

  ASSERT_EQ(16, game._cState.size());
  for (int i = 0; i < game._cState.size(); i++) {
    ASSERT_EQ(0, game._cState[i]);
  }

  ASSERT_NE(0, game._tileColor[0]);
  for (int i = 2; i <= 131072; i *= 2) {
    ASSERT_NE(0, game._tileColor[i]);
    ASSERT_NE(0, game._numberColor[i]);
    ASSERT_NE(0, game._overhead[i]);
  }

  ASSERT_NE(0, game._width);
  ASSERT_NE(0, game._hight);
  ASSERT_NE(0, game._offsetX);
  ASSERT_NE(0, game._offsetY);
}

TEST(Game2048, initializeUndo) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game._undoStates = 5;
  game.initializeGame();
  game.initializeUndo();

  for (int i = 0; i < game._undoStates; i++) {
    ASSERT_NE(0, game._states[i].size());
    ASSERT_EQ(0, game._scores[i]);
  }
}

TEST(Game2048, isWin) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  ASSERT_FALSE(game.isWin());
  game._cState[4] = 2048;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 4096;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 8192;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 16384;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 32768;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 65536;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 131072;
  ASSERT_TRUE(game.isWin());

  game._cState[4] = 0;
  game._cState[11] = 2048;
  game._cState[14] = 2048;
  ASSERT_TRUE(game.isWin());

  game._cState[11] = 1024;
  game._cState[14] = 1024;
  ASSERT_FALSE(game.isWin());
}

TEST(Game2048, isLose) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();
  ASSERT_FALSE(game.isLose());

  for (int i = 0; i < game._cState.size(); i++) {
    game._cState[i] = 2;
  }
  ASSERT_FALSE(game.isLose());

  game._cState[0] = 4;
  game._cState[2] = 4;
  game._cState[5] = 4;
  game._cState[7] = 4;
  game._cState[8] = 4;
  game._cState[10] = 4;
  game._cState[13] = 4;
  game._cState[15] = 4;
  ASSERT_TRUE(game.isLose());

  game._cState[0] = 0;
  ASSERT_FALSE(game.isLose());
}

TEST(Game2048, movePossible) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();
  ASSERT_FALSE(game.movePossible(up));
  ASSERT_FALSE(game.movePossible(down));
  ASSERT_FALSE(game.movePossible(left));
  ASSERT_FALSE(game.movePossible(right));

  game._cState[0] = 4;
  ASSERT_FALSE(game.movePossible(up));
  ASSERT_TRUE(game.movePossible(down));
  ASSERT_FALSE(game.movePossible(left));
  ASSERT_TRUE(game.movePossible(right));

  game._cState[0] = 0;
  game._cState[5] = 2;
  ASSERT_TRUE(game.movePossible(up));
  ASSERT_TRUE(game.movePossible(down));
  ASSERT_TRUE(game.movePossible(left));
  ASSERT_TRUE(game.movePossible(right));

  for (int i = 0; i < game._cState.size(); i++) {
    game._cState[i] = 2;
  }
  ASSERT_FALSE(game.movePossible(up));
  ASSERT_FALSE(game.movePossible(down));
  ASSERT_FALSE(game.movePossible(left));
  ASSERT_FALSE(game.movePossible(right));

  game._cState[0] = 0;
  ASSERT_TRUE(game.movePossible(up));
  ASSERT_FALSE(game.movePossible(down));
  ASSERT_TRUE(game.movePossible(left));
  ASSERT_FALSE(game.movePossible(right));
}

TEST(Game2048, moveDirection) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  game._cState[0] = 2;
  game.moveDirection(right);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(2, game._cState[3]);

  game.moveDirection(down);
  ASSERT_EQ(0, game._cState[3]);
  ASSERT_EQ(2, game._cState[15]);

  game.moveDirection(left);
  ASSERT_EQ(0, game._cState[15]);
  ASSERT_EQ(2, game._cState[14]);

  game.moveDirection(up);
  ASSERT_EQ(0, game._cState[14]);
  ASSERT_EQ(2, game._cState[10]);
  game._cState[10] = 0;

  game._cState[0] = 2;
  game._cState[1] = 4;
  game._cState[2] = 8;
  game._cState[3] = 16;
  game.moveDirection(right);
  ASSERT_EQ(2, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(8, game._cState[2]);
  ASSERT_EQ(16, game._cState[3]);

  game.moveDirection(left);
  ASSERT_EQ(2, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(8, game._cState[2]);
  ASSERT_EQ(16, game._cState[3]);

  game.moveDirection(up);
  ASSERT_EQ(2, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(8, game._cState[2]);
  ASSERT_EQ(16, game._cState[3]);

  game.moveDirection(down);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(0, game._cState[2]);
  ASSERT_EQ(0, game._cState[3]);
  ASSERT_EQ(2, game._cState[12]);
  ASSERT_EQ(4, game._cState[13]);
  ASSERT_EQ(8, game._cState[14]);
  ASSERT_EQ(16, game._cState[15]);
}

TEST(Game2048, combinePossible) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  game._cState[1] = 2;
  game._cState[2] = 2;
  ASSERT_TRUE(game.combinePossible(left));
  ASSERT_TRUE(game.combinePossible(right));
  ASSERT_FALSE(game.combinePossible(up));
  ASSERT_FALSE(game.combinePossible(down));
  ASSERT_TRUE(game.combinePossible(universal));

  game._cState[2] = 0;
  game._cState[1] = 2;
  game._cState[5] = 2;
  ASSERT_FALSE(game.combinePossible(left));
  ASSERT_FALSE(game.combinePossible(right));
  ASSERT_TRUE(game.combinePossible(up));
  ASSERT_TRUE(game.combinePossible(down));
  ASSERT_TRUE(game.combinePossible(universal));

  game._cState[5] = 0;
  game._cState[15] = 2;
  ASSERT_FALSE(game.combinePossible(left));
  ASSERT_FALSE(game.combinePossible(right));
  ASSERT_FALSE(game.combinePossible(up));
  ASSERT_FALSE(game.combinePossible(down));
  ASSERT_FALSE(game.combinePossible(universal));
}

TEST(Game2048, combineTiles) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  game._cState[0] = 2;
  game._cState[1] = 2;
  game.combineTiles(left);
  ASSERT_EQ(4, game._cState[0]);
  ASSERT_EQ(0, game._cState[1]);

  game._cState[0] = 2;
  game._cState[1] = 2;
  game.combineTiles(right);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);

  game._cState[1] = 2;
  game._cState[5] = 2;
  game.combineTiles(up);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(0, game._cState[5]);

  game._cState[1] = 2;
  game._cState[5] = 2;
  game.combineTiles(down);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(4, game._cState[5]);

  game._cState[1] = 2;
  game._cState[5] = 2;
  game._cState[9] = 2;
  game._cState[13] = 2;
  game.combineTiles(down);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(4, game._cState[5]);
  ASSERT_EQ(0, game._cState[9]);
  ASSERT_EQ(4, game._cState[13]);

  game._cState[1] = 2;
  game._cState[5] = 2;
  game._cState[9] = 2;
  game._cState[13] = 2;
  game.combineTiles(up);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(0, game._cState[5]);
  ASSERT_EQ(4, game._cState[9]);
  ASSERT_EQ(0, game._cState[13]);

  game._cState[1] = 0;
  game._cState[5] = 0;
  game._cState[9] = 0;
  game._cState[13] = 0;

  game._cState[0] = 2;
  game._cState[1] = 2;
  game._cState[2] = 2;
  game._cState[3] = 2;
  game.combineTiles(right);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(0, game._cState[2]);
  ASSERT_EQ(4, game._cState[3]);

  game._cState[0] = 2;
  game._cState[1] = 2;
  game._cState[2] = 2;
  game._cState[3] = 2;
  game.combineTiles(left);
  ASSERT_EQ(4, game._cState[0]);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(4, game._cState[2]);
  ASSERT_EQ(0, game._cState[3]);
}

TEST(Game2048, resetGame) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  game._cState[0] = 2048;
  game._cState[3] = 2048;
  game._cState[5] = 2048;
  game._cState[10] = 2048;
  game._stateCounter = 5;
  game._turn = 200;
  game._score = 200000;

  game.resetGame();
  for (int i = 0; i < game._cState.size(); i++) {
    ASSERT_EQ(0, game._cState[i]);
  }
  ASSERT_EQ(0, game._stateCounter);
  ASSERT_EQ(0, game._turn);
  ASSERT_EQ(0, game._score);
}

TEST(Game2048, updateState) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game._undoStates = 4;
  game.initializeGame();
  game.initializeUndo();

  // game.updateState(1);
  game._cState[0] = 2;
  game.updateState(1);
  game._cState[1] = 4;
  game.updateState(1);

  ASSERT_EQ(2, game._cState[0]);
  ASSERT_EQ(4, game._cState[1]);
  ASSERT_EQ(2, game._turn);
  ASSERT_EQ(2, game._stateCounter);

  game.updateState(-1);
  ASSERT_EQ(2, game._cState[0]);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(1, game._turn);
  ASSERT_EQ(1, game._stateCounter);

  game.updateState(-1);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(0, game._cState[1]);
  ASSERT_EQ(0, game._turn);
  ASSERT_EQ(0, game._stateCounter);
}

TEST(Game2048, addTwoOrFour) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();

  int sum = 0;
  for (int i = 0; i < game._cState.size(); i++) {
    sum += game._cState[i];
  }
  ASSERT_EQ(0, sum);

  game.addTwoOrFour();
  for (int i = 0; i < game._cState.size(); i++) {
    sum += game._cState[i];
  }
  ASSERT_LT(0, sum);
}

TEST(Game2048, makeMove) {
  Game2048 game;
  COLS = 200;
  LINES = 200;
  game.initializeGame();
  int sum = 0;
  for (int i = 0; i < game._cState.size(); i++) {
    sum += game._cState[i];
  }
  ASSERT_EQ(0, sum);

  game._cState[0] = 2;
  game._cState[14] = 4;
  game.makeMove(right);
  ASSERT_EQ(0, game._cState[0]);
  ASSERT_EQ(0, game._cState[14]);
  ASSERT_EQ(2, game._cState[3]);
  ASSERT_EQ(4, game._cState[15]);
  for (int i = 0; i < game._cState.size(); i++) {
    sum += game._cState[i];
  }
  ASSERT_LT(6, sum);

  game.resetGame();

  game._cState[2] = 4;
  game._cState[10] = 4;
  game.makeMove(up);
  ASSERT_EQ(8, game._cState[2]);
  ASSERT_EQ(0, game._cState[10]);
  for (int i = 0; i < game._cState.size(); i++) {
    sum += game._cState[i];
  }
  ASSERT_LT(8, sum);
}
