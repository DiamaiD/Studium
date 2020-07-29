// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef GAME2048_H_
#define GAME2048_H_

#include <gtest/gtest.h>
#include <ncurses.h>
#include <vector>
#include <array>
#include <unordered_map>

using std::vector;
using std::array;
using std::unordered_map;


class Game2048 {
 public:
  // constructor and destructor (not default)
  Game2048();
  ~Game2048();

  // get the parameters
  void parseCommandLineArguments(int argc, char** argv);
  // print the usage if the parameters are wrong
  void printUsageAndExit() const;

  // start the game
  void play();

 private:
  int _turn;
  int _score;
  int _undoStates;
  int _tileSize;
  int _width;
  int _hight;
  int _offsetX;
  int _offsetY;
  int _stateCounter;

  // color map for tiles
  unordered_map<int, int> _tileColor;
  // color map for numbers
  unordered_map<int, int> _numberColor;
  // this map is needed for the exact position of numbers depending
  // on the numbers size a.k.a. an offset of the number in the tile
  unordered_map<int, int> _overhead;

  // different states for undo function
  vector<array<int, 16> > _states;

  // different scores for undo function
  vector<int> _scores;

  // current state
  array<int, 16> _cState;


  // intialize encurses
  void initializeEncurses() const;
  // prepare the game
  void initializeGame();
  // prepare the undo function
  void initializeUndo();

  // draw functions
  void drawBoarder() const;
  void drawState();
  void drawScoreAndTurn() const;
  void printWin() const;
  void printLose() const;
  // delte the win or lose message
  void removeWinOrLoseMessage();

  // get the input of the player
  int getInput() const;

  // call a series of functions to make a move
  void makeMove(const int& key);
  // called with 1, update the the current state, turn and score
  // called with -1, undo the current state to the previous one
  void updateState(int x);
  // call updateState with x = -1
  void undoMove();

  // check if current state is a losing position
  bool isLose() const;
  // check if there is a 2048 or higher on the board a.k.a. a win
  bool isWin() const;
  // check if you can combine some tiles in the given direction
  bool combinePossible(const int& key) const;
  // check if you can move some tile in the given direction
  bool movePossible(const int& key) const;

  // move tiles in the given direction
  bool moveDirection(const int& key);
  // combine tiles in the given direction
  void combineTiles(const int& key);

  // reset the game to a blank board with score = 0 and turn = 1
  void resetGame();

  // add 2 or 4 to the board on an empty tile
  void addTwoOrFour();

  FRIEND_TEST(Game2048, constructor);
  FRIEND_TEST(Game2048, printUsageAndExit);
  FRIEND_TEST(Game2048, parseCommandLineArguments);
  FRIEND_TEST(Game2048, parseCommandLineArgumentsShort);
  FRIEND_TEST(Game2048, parseCommandLineWithNoArguments);
  FRIEND_TEST(Game2048, initializeGame);
  FRIEND_TEST(Game2048, initializeUndo);
  FRIEND_TEST(Game2048, isWin);
  FRIEND_TEST(Game2048, isLose);
  FRIEND_TEST(Game2048, movePossible);
  FRIEND_TEST(Game2048, moveDirection);
  FRIEND_TEST(Game2048, combinePossible);
  FRIEND_TEST(Game2048, combineTiles);
  FRIEND_TEST(Game2048, resetGame);
  FRIEND_TEST(Game2048, updateState);
  FRIEND_TEST(Game2048, addTwoOrFour);
  FRIEND_TEST(Game2048, makeMove);
};

#endif  // GAME2048_H_
