// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef MARKETSIMULATOR_H_
#define MARKETSIMULATOR_H_

#include <gtest/gtest.h>
#include "./String.h"
#include "./Trader.h"

class MarketSimulator {
 private:
  double _seedMoney;
  bool _verbose;
  const char* _inputFileName;

  void printUsageAndExit() const;

 public:
  MarketSimulator();
  ~MarketSimulator();

  void parseCommandLineArguments(int argc, char** argv);

  void simulate(Trader* tr) const;

  FRIEND_TEST(MarketSimulatorTest, constructor);
  FRIEND_TEST(MarketSimulatorTest, printUsageAndExit);
  FRIEND_TEST(MarketSimulatorTest, parseCommandLineArguments);
  FRIEND_TEST(MarketSimulatorTest, parseCommandLineArgumentsShorthand);
  FRIEND_TEST(MarketSimulatorTest, parseCommandLineArgumentsWithNoArguments);
  FRIEND_TEST(MarketSimulatorTest, parseCommandLineArgumentsNoFileName);
  FRIEND_TEST(MarketSimulatorTest, parseCommandLineArgumentsOnlyFileName);
  FRIEND_TEST(MarketSimulatorTest, simulate);
  FRIEND_TEST(MarketSimulatorTest, simulateWithNonExistingInputFile);
  friend class Trader;
};

#endif  // MARKETSIMULATOR_H_
