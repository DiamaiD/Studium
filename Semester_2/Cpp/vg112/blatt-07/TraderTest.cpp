// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//          Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Trader.h"

// _____________________________________________________________________________
TEST(TraderTest, constructor) {
  Trader trader;
  ASSERT_FLOAT_EQ(0, trader._money);
  ASSERT_FLOAT_EQ(0, trader._seedMoney);
  ASSERT_EQ(0, trader._numBitcoins);
  ASSERT_FALSE(trader._verbose);
  ASSERT_FLOAT_EQ(0.0, trader._lastPrices[0]);
  ASSERT_FLOAT_EQ(0.0, trader._lastPrices[1]);
  ASSERT_FLOAT_EQ(0.0, trader._lastPrices[2]);
}

// _____________________________________________________________________________
TEST(TraderTest, trade) {
  Trader trader;
  trader._money = 10;

  // Check if the trader buys on 3 price increases.
  trader.trade(1.2);
  ASSERT_FLOAT_EQ(10, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);
  trader.trade(1.2);  // No increase -> Don't buy.
  ASSERT_FLOAT_EQ(10, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);
  trader.trade(3.5);  // First increase -> Don't buy.
  ASSERT_FLOAT_EQ(10, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);
  trader.trade(4.2);  // Second increase -> Don't buy.
  ASSERT_FLOAT_EQ(10, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);
  trader.trade(4.3);  // Third increase -> Buy!
  ASSERT_FLOAT_EQ(5.7, trader._money);
  ASSERT_FLOAT_EQ(1, trader._numBitcoins);
  trader.trade(4.7);  // Another increase -> Buy!
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(6);  // Another increase, but not enough money -> Don't buy.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);

  // Check if the trader sells on 3 price decreases.
  trader.trade(5.3);  // First decrease.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(5.2);  // Second decrease.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(5.2);  // No decrease.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(4.7);  // First decrease.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(4.3);  // Second decrease.
  ASSERT_FLOAT_EQ(1.0, trader._money);
  ASSERT_FLOAT_EQ(2, trader._numBitcoins);
  trader.trade(3.6);  // Third decrease -> Sell.
  ASSERT_FLOAT_EQ(4.6, trader._money);
  ASSERT_FLOAT_EQ(1, trader._numBitcoins);
  trader.trade(3.2);  // Fourth decrease -> Sell.
  ASSERT_FLOAT_EQ(7.8, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);
  trader.trade(3.1);  // Fifth decrease, but no bitcoins anymore -> Don't sell.
  ASSERT_FLOAT_EQ(7.8, trader._money);
  ASSERT_FLOAT_EQ(0, trader._numBitcoins);

  // Check if the trader do nothing if the price is fluctuating.
  trader._money = 20;
  trader._numBitcoins = 20;
  trader.trade(16);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
  trader.trade(14);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
  trader.trade(16);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
  trader.trade(14);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
  trader.trade(16);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
  trader.trade(14);
  ASSERT_FLOAT_EQ(20, trader._money);
  ASSERT_FLOAT_EQ(20, trader._numBitcoins);
}
