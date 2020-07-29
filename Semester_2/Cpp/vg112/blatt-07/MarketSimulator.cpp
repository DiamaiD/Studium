// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <getopt.h>
#include "./String.h"
#include "./Trader.h"
#include "./MarketSimulator.h"

MarketSimulator::MarketSimulator() {
  _verbose = false;
  _seedMoney = 0;
  _inputFileName = "";
}

MarketSimulator::~MarketSimulator() {
}

void MarketSimulator::printUsageAndExit() const {
  fprintf(stderr,
    "Usage: ./MarketSimulatorMain [options] <file>\n"
    "\n"
    " --seed-money, -s <arg>: specify how much money to spend\n"
    " --verbose, -v <arg>: print every transaction if <arg> == true\n");
  exit(1);
}

void MarketSimulator::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    { "seed-money", 1, NULL, 's'},
    { "verbose", 0, NULL, 'v'},
    { NULL, 0, NULL, 0 }
  };
  optind = 1;
  while (true) {
    char c = getopt_long(argc, argv, "s:v", options, NULL);
    if (c == -1) break;
    switch (c) {
      case 's':
        _seedMoney = atoi(optarg);
        break;
      case 'v':
        _verbose = true;
        break;
    }
  }
  if (_seedMoney == 0) _seedMoney = 1000;
  if (optind >= argc) printUsageAndExit();
  _inputFileName = argv[optind];
}

void MarketSimulator::simulate(Trader* tr) const {
  FILE* file = fopen(_inputFileName, "r");
  if (file == NULL) {
    perror("Error: Could not open input file");
    exit(1);
  }
  tr->_money = _seedMoney;
  tr->_seedMoney = _seedMoney;
  tr->_verbose = _verbose;
  StringArray strarray;
  String str;
  const int MAX = 1000;
  char line[MAX + 1];
  while (true) {
    fgets(line, MAX, file);
    str.set(line);
    if (feof(file)) break;
    str.split('\t', &strarray);
    tr->trade(strarray.get(1).toFloat());
  }
  fclose(file);
}
