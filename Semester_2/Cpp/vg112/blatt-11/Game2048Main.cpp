// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <string>
#include <vector>
#include <iostream>
#include "./Game2048.h"

using std::string;
using std::vector;

int main(int argc, char** argv) {
  Game2048 game;
  game.parseCommandLineArguments(argc, argv);
  game.play();
}
