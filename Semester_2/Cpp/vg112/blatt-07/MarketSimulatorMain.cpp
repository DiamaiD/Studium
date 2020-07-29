// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include "./MarketSimulator.h"
#include "./Trader.h"

int main(int argc, char** argv) {
  MarketSimulator market;
  market.parseCommandLineArguments(argc, argv);
  Trader trader;
  market.simulate(&trader);
  trader.printStatistics();
}
