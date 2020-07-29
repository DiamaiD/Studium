// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <getopt.h>
#include <ncurses.h>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include "./Game2048.h"

using std::vector;
using std::unordered_map;

#define KEY_ESC 27
#define up 259
#define right 261
#define down 258
#define left 260
#define universal 1000

// ___________________________________________________________________________
Game2048::Game2048() {
  _undoStates = 0;
  _stateCounter = 0;
  _turn = 0;
  _score = 0;
}

// ___________________________________________________________________________
Game2048::~Game2048() {
  endwin();
}

// ___________________________________________________________________________
void Game2048::printUsageAndExit() const {
  fprintf(stderr,
    "Usage: ./Game2048Main [options]\n"
    "\n"
    " --undo-states, -u <arg>: specify the amount of states you can undo\n");
  exit(1);
}

// ___________________________________________________________________________
void Game2048::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    { "undo-states", 1, NULL, 'u'},
    { NULL, 0, NULL, 0 }
  };
  optind = 1;
  while (true) {
    char c = getopt_long(argc, argv, "u:", options, NULL);
    if (c == -1) break;
    switch (c) {
      case 'u':
        _undoStates = atoi(optarg);
        break;
    }
  }
  if (optind < argc) printUsageAndExit();
}

// ___________________________________________________________________________
void Game2048::initializeGame() {
  // init colors
  start_color();

  // colors for the tiles                     // foreground     background
  init_pair(1, 8, COLOR_BLACK);               // Grey,          Black
  init_pair(2, COLOR_WHITE, COLOR_BLACK);     // White,         Black
  init_pair(3, 14, COLOR_BLACK);              // Bright Cyan,   Black
  init_pair(4, COLOR_CYAN, COLOR_BLACK);      // Cyan,          Black
  init_pair(5, 12, COLOR_BLACK);              // Bright Blue,   Black
  init_pair(6, 11, COLOR_BLACK);              // Bright Yellow, Black
  init_pair(7, COLOR_YELLOW, COLOR_BLACK);    // Yellow,        Black
  init_pair(8, COLOR_RED, COLOR_BLACK);       // Red,           Black
  init_pair(9, 9, COLOR_BLACK);               // Bright Red,    Black
  init_pair(10, 15, COLOR_BLACK);             // Bright White,  Black
  init_pair(11, COLOR_MAGENTA, COLOR_BLACK);  // Pink,          Black
  init_pair(12, 13, COLOR_BLACK);             // Bright Pink,   Black
  init_pair(13, COLOR_GREEN, COLOR_BLACK);    // Green,         Black
  init_pair(14, 10, COLOR_BLACK);             // Bright Green,  Black

  // reverse the colors for the number in the tiles
  init_pair(15, COLOR_BLACK, 8);              // Black, Grey
  init_pair(16, COLOR_BLACK, COLOR_WHITE);    // Black, White
  init_pair(17, COLOR_BLACK, 14);             // Black, Bright Cyan
  init_pair(18, COLOR_BLACK, COLOR_CYAN);     // Black, Cyan
  init_pair(19, COLOR_WHITE, 12);             // Black, Bright Blue
  init_pair(20, COLOR_BLACK, 11);             // Black, Bright Yellow
  init_pair(21, COLOR_BLACK, COLOR_YELLOW);   // Black, Yellow
  init_pair(22, COLOR_BLACK, COLOR_RED);      // Black, Red
  init_pair(23, COLOR_BLACK, 9);              // Black, Bright Red
  init_pair(24, COLOR_BLACK, 15);             // Black, Bright White
  init_pair(25, COLOR_BLACK, COLOR_MAGENTA);  // Black, Pink
  init_pair(26, COLOR_BLACK, 13);             // Black, Bright Pink
  init_pair(27, COLOR_BLACK, COLOR_GREEN);    // Black, Green
  init_pair(28, COLOR_BLACK, 10);             // Black, Bright Green

  // fill the color map for the tile foreground color
  _tileColor[0] = 2;
  _tileColor[2] = 3;
  _tileColor[4] = 4;
  _tileColor[8] = 5;
  _tileColor[16] = 6;
  _tileColor[32] = 7;
  _tileColor[64] = 8;
  _tileColor[128] = 9;
  _tileColor[256] = 10;
  _tileColor[512] = 11;
  _tileColor[1024] = 12;
  _tileColor[2048] = 13;
  _tileColor[4096] = 14;
  _tileColor[8192] = 3;
  _tileColor[16384] = 4;
  _tileColor[32768] = 5;
  _tileColor[65536] = 7;
  _tileColor[131072] = 9;

  // fill the color map of the number foreground and background color
  _numberColor[2] = 17;
  _numberColor[4] = 18;
  _numberColor[8] = 19;
  _numberColor[16] = 20;
  _numberColor[32] = 21;
  _numberColor[64] = 22;
  _numberColor[128] = 23;
  _numberColor[256] = 24;
  _numberColor[512] = 25;
  _numberColor[1024] = 26;
  _numberColor[2048] = 27;
  _numberColor[4096] = 28;
  _numberColor[8192] = 17;
  _numberColor[16384] = 18;
  _numberColor[32768] = 19;
  _numberColor[65536] = 21;
  _numberColor[131072] = 23;

  // check if terminal is too small for the game, and assert if so
  assert(("Terminal too small for this game, make it bigger!!!",
         (5 * 4 * 2 + 10) < COLS));
  assert(("Terminal too small for this game, make it bigger!!!",
         (5 * 4 + 5 + 1) < LINES));

  // chose the tile size depending on the size of the terminal
  if (((7 * 4 * 2 + 10) < COLS) && ((7 * 4 + 5) < LINES)) {
    _tileSize = 7;
  } else {
    _tileSize = 5;
  }

  // compute the size of the game and the offsets (needed later to
  // center the game)
  _width = _tileSize * 4 * 2 + 10;
  _hight = _tileSize * 4 + 5;
  _offsetX = (COLS - _width) / 2;
  _offsetY = (LINES - _hight - 2) / 2;

  // fill the current state of the game with zeros
  for (size_t i = 0; i < _cState.size(); i++) {
    _cState[i] = 0;
  }

  // fill the _overhead of the position of the number,
  // needed for centering the number in the tile
  _overhead[2] = _tileSize + 1;
  _overhead[4] = _tileSize + 1;
  _overhead[8] = _tileSize + 1;
  _overhead[16] = _tileSize + 1;
  _overhead[32] = _tileSize + 1;
  _overhead[64] = _tileSize + 1;
  _overhead[128] = _tileSize;
  _overhead[256] = _tileSize;
  _overhead[512] = _tileSize;
  _overhead[1024] = _tileSize;
  _overhead[2048] = _tileSize;
  _overhead[4096] = _tileSize;
  _overhead[8192] = _tileSize;
  _overhead[16384] = _tileSize - 1;
  _overhead[32768] = _tileSize - 1;
  _overhead[65536] = _tileSize - 1;
  _overhead[131072] = _tileSize - 1;
}

// ___________________________________________________________________________
void Game2048::initializeUndo() {
  // fill the undo states with the current state
  for (size_t i = 0; i < _undoStates; i++) {
    _states.push_back(_cState);
  }
  // fill the undo scores with the current, which is zero
  for (size_t i = 0; i < _undoStates; i++) {
    _scores.push_back(_score);
  }
}

// ___________________________________________________________________________
void Game2048::initializeEncurses() const {
  initscr();              // Initializiation.
  cbreak();               // Don't wait for RETURN.
  noecho();               // Don't echo key presses on screen.
  curs_set(false);        // Don't show the cursor.
  nodelay(stdscr, true);  // Don't wait until key pressed.
  keypad(stdscr, true);   // For KEY_LEFT, KEY_UP, etc.
}

// ___________________________________________________________________________
bool Game2048::isWin() const {
  for (int i = 0; i < _cState.size(); i++) {
    if (_cState[i] >= 2048) return true;
  }
  return false;
}

// ___________________________________________________________________________
void Game2048::drawBoarder() const {
  // paint the boarders of the game
  attron(A_REVERSE);
  attron(COLOR_PAIR(1));
  int end = _width * _hight;
  for (int i = 0; i < end; i++) {
    if ( (i / _width % (_tileSize + 1)) == 0 ||
         (i % _width % (_tileSize * 2 + 2)) == 0 ||
         (i % _width % (_tileSize * 2 + 2)) == 1) {
      mvprintw(i / (_width) + _offsetY, i % (_width) + _offsetX, " ");
    }
  }
  attroff(COLOR_PAIR(1));
  attroff(A_REVERSE);
}

// ___________________________________________________________________________
void Game2048::drawState() {
  attron(A_REVERSE);
  int end = _hight * _width;

  // paint the tiles to the corresponding color of the number
  for (int i = 0; i < _cState.size(); i++) {
    int deltax = (_tileSize * 2 + 2) * (i % 4) + 2;
    int deltay = (_tileSize + 1) * (i / 4) + 1;
    attron(COLOR_PAIR(_tileColor[_cState[i]]));
    for (int y = 0; y < _tileSize; y++) {
      for (int x = 0; x < _tileSize * 2; x++) {
        mvprintw(deltay + y + _offsetY, deltax + x + _offsetX, " ");
      }
    }
    attroff(COLOR_PAIR(_tileColor[_cState[i]]));
  }

  // fill in the numbers on the right position
  attroff(A_REVERSE);
  for (int i = 0; i < _cState.size(); i++) {
    if (_cState[i] == 0) continue;
    attron(COLOR_PAIR(_numberColor[_cState[i]]));
    mvprintw(i / 4 * (_tileSize+1) + _tileSize / 2 + 1 + _offsetY,
             i % 4 * (_tileSize*2 + 2) + _overhead.at(_cState[i]) + _offsetX,
             std::to_string(_cState[i]).c_str());
    attroff(COLOR_PAIR(_numberColor[_cState[i]]));
  }
}

// ___________________________________________________________________________
void Game2048::drawScoreAndTurn() const {
  mvprintw(_offsetY + _hight, _offsetX, "Score: %d        ", _score);
  mvprintw(_offsetY + _hight, _offsetX + (_tileSize*2 + 2) * 2 + 2,
           "Turn: %d     ", _turn+1);
}

// ___________________________________________________________________________
bool Game2048::isLose() const {
  // check if there are non filled tiles
  for (int i = 0; i < _cState.size(); i++) {
    if (_cState[i] == 0) return false;
  }
  // check if you can combine something in any direction
  if (combinePossible(universal)) return false;
  return true;
}

// ___________________________________________________________________________
void Game2048::printLose() const {
  mvprintw(_offsetY + _hight + 1, _offsetX + (_width - 23) / 2,
           "Game over: press [n] to start over");
}

// ___________________________________________________________________________
void Game2048::printWin() const {
  mvprintw(_offsetY + _hight + 1, _offsetX + (_width - 23) / 2,
           "Congratulations you won!          ");
}

void Game2048::removeWinOrLoseMessage() {
  mvprintw(_offsetY + _hight + 1, _offsetX + (_width - 23) / 2,
           "                                  ");
}

// ___________________________________________________________________________
bool Game2048::moveDirection(const int& key) {
  int deltaX = 0;
  int deltaY = 0;
  int xStart = 0;
  int yStart = 0;
  int xEnd = 4;
  int yEnd = 4;
  // prepare the start and end points of the multi array of the state
  if (key == right) {
    deltaX = 1;
    xEnd = 3;
  } else if (key == left) {
    deltaX = -1;
    xStart = 1;
  } else if (key == up) {
    deltaY = -1;
    yStart = 1;
  } else if (key == down) {
    deltaY = 1;
    yEnd = 3;
  }
  bool moved = false;
  // move the tiles if possible one tile to the given direction
  for (int y = yStart; y < yEnd; y++) {
    for (int x = xStart; x < xEnd; x++) {
      if ((_cState[y*4+x] > 0) && (_cState[(y+deltaY)*4+x+deltaX] == 0)) {
        moved = true;
        _cState[(y+deltaY)*4+x+deltaX] = _cState[y*4+x];
        _cState[y*4+x] = 0;
      }
    }
  }
  return moved;
}

// ___________________________________________________________________________
bool Game2048::combinePossible(const int& key) const {
  if ((key == left) || (key == right) || (key == universal)) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 3; x++) {
        if (_cState[y*4+x] != 0 && _cState[y*4+x] == _cState[y*4+x+1]) {
          return true;
        }
      }
    }
  }
  if ((key == down) || (key == up) || (key == universal)) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 4; x++) {
        if (_cState[y*4+x] != 0 && _cState[y*4+x] == _cState[(y+1)*4+x]) {
          return true;
        }
      }
    }
  }
  return false;
}

// ___________________________________________________________________________
bool Game2048::movePossible(const int& key) const {
  if (key == left) {
    for (int y = 0; y < 4; y++) {
      for (int x = 3; x > 0; x--) {
        if (_cState[y*4+x] > 0 && _cState[y*4+x-1] == 0) {
          return true;
        }
      }
    }
  }
  if (key == right) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 3; x++) {
        if (_cState[y*4+x] > 0 && _cState[y*4+x+1] == 0) {
          return true;
        }
      }
    }
  }
  if (key == up) {
    for (int y = 3; y > 0; y--) {
      for (int x = 0; x < 4; x++) {
        if (_cState[y*4+x] > 0 && _cState[(y-1)*4+x] == 0) {
          return true;
        }
      }
    }
  }
  if (key == down) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 4; x++) {
        if (_cState[y*4+x] > 0 && _cState[(y+1)*4+x] == 0) {
          return true;
        }
      }
    }
  }
  return false;
}

// ___________________________________________________________________________
void Game2048::combineTiles(const int& key) {
  if (key == right) {
    for (int y = 0; y < 4; y++) {
      for (int x = 3; x > 0; x--) {
        if (_cState[y*4+x] == _cState[y*4+x-1]) {
          _cState[y*4+x] *= 2;
          _cState[y*4+x-1] = 0;
          _score += _cState[y*4+x];
        }
      }
    }
  }
  if (key == left) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 3; x++) {
        if (_cState[y*4+x] == _cState[y*4+x+1]) {
          _cState[y*4+x] *= 2;
          _cState[y*4+x+1] = 0;
          _score += _cState[y*4+x];
        }
      }
    }
  }
  if (key == down) {
    for (int y = 3; y > 0; y--) {
      for (int x = 0; x < 4; x++) {
        if (_cState[y*4+x] == _cState[(y-1)*4+x]) {
          _cState[y*4+x] *= 2;
          _cState[(y-1)*4+x] = 0;
          _score += _cState[y*4+x];
        }
      }
    }
  }
  if (key == up) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 4; x++) {
        if (_cState[y*4+x] == _cState[(y+1)*4+x]) {
          _cState[y*4+x] *= 2;
          _cState[(y+1)*4+x] = 0;
          _score += _cState[y*4+x];
        }
      }
    }
  }
}

// ___________________________________________________________________________
void Game2048::resetGame() {
  // reset the board to a blank one without numbers
  for (int i = 0; i < _cState.size(); i++) {
    _cState[i] = 0;
  }
  // remove the win or lose message
  removeWinOrLoseMessage();

  _stateCounter = 0;
  _turn = 0;
  _score = 0;
}

// ___________________________________________________________________________
void Game2048::updateState(int x = 1) {
  // undo move to the previous one
  if (x == -1 && _undoStates > 0) {
    if ((_stateCounter - 1) >= 0) {
      _stateCounter -= 1;
      _turn -= 1;
    }
    _cState = _states[_stateCounter];
    _score = _scores[_stateCounter];
  }
  // do the move, update the states and score for the undo function
  if (x == 1) _turn += 1;
  if (x == 1 && _undoStates > 0) {
    if (_stateCounter < _undoStates) {
      _stateCounter += 1;
      _states[_stateCounter] = _cState;
      _scores[_stateCounter] = _score;
    } else {
      for (int i = 0; i < _stateCounter; i++) {
        _states[i] = _states[i+1];
        _scores[i] = _scores[i+1];
      }
      _states[_stateCounter] = _cState;
      _scores[_stateCounter] = _score;
    }
  }
}

// ___________________________________________________________________________
void Game2048::undoMove() {
  updateState(-1);
  removeWinOrLoseMessage();
}

// ___________________________________________________________________________
void Game2048::addTwoOrFour() {
  int random_variable = drand48() * 100;
  int tile;
  if (random_variable < 10) {
    tile = 4;
  } else {
    tile = 2;
  }
  while (true) {
    int random_variable = drand48() * _cState.size();
    if (_cState[random_variable] == 0) {
      _cState[random_variable] = tile;
      break;
    }
  }
}

// ___________________________________________________________________________
int Game2048::getInput() const {
  return getch();
}

// ___________________________________________________________________________
void Game2048::makeMove(const int& key) {
  while (moveDirection(key)) {}
  combineTiles(key);
  while (moveDirection(key)) {}
  addTwoOrFour();
  updateState();
}

// ___________________________________________________________________________
void Game2048::play() {
  // prepare the game for the loop
  initializeEncurses();
  initializeGame();
  drawBoarder();
  addTwoOrFour();
  addTwoOrFour();
  initializeUndo();
  drawState();

  while (true) {
    // get keyboard input of the player
    int key = getInput();

    // if ESC is pressed by player end the game
    if (key == KEY_ESC) break;

    // display message if Won
    if (isWin()) printWin();
    // display message if Game over
    if (isLose()) printLose();

    // check if player pressed a directional key
    if (key == up || key == down || key == left || key == right) {
      // move or combine in the intended direction if possible
      if (movePossible(key) || combinePossible(key)) {
        makeMove(key);
      } else {
        continue;  // restart the loop otherwise
      }
    }

    // restart the Game
    if (key == 'n') {
      resetGame();
      addTwoOrFour();
      addTwoOrFour();
    }

    // jump to previous move
    if (key == 'u') {
      undoMove();
    }

    // draw the current board, score and turn
    drawState();
    drawScoreAndTurn();
  }
}
