// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef TRADER_H_
#define TRADER_H_

#include <gtest/gtest.h>

class Trader {
 private:
  double _money;
  double _seedMoney;
  int _numBitcoins;
  bool _verbose;
  double* _lastPrices;

 public:
  Trader();
  ~Trader();

  void trade(double exchange);

  void printStatistics() const;

  FRIEND_TEST(TraderTest, constructor);
  FRIEND_TEST(TraderTest, trade);
  FRIEND_TEST(MarketSimulatorTest, simulate);
  FRIEND_TEST(MarketSimulatorTest, simulateWithNonExistingInputFile);
  friend class MarketSimulator;
};

#endif  // TRADER_H_
