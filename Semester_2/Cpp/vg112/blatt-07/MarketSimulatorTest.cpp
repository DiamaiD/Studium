// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./MarketSimulator.h"

// _____________________________________________________________________________
TEST(MarketSimulatorTest, constructor) {
  MarketSimulator market;
  ASSERT_STREQ("", market._inputFileName);
  ASSERT_EQ(0, market._seedMoney);
  ASSERT_FALSE(market._verbose);
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, printUsageAndExit) {
  MarketSimulator market;
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(market.printUsageAndExit(), "Usage: ./MarketSimulatorMain .*");
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, parseCommandLineArguments) {
  MarketSimulator market;
  int argc = 5;
  char* argv[5] = {
    const_cast<char*>("./MarketSimulatorMain"),
    const_cast<char*>("--seed-money"),
    const_cast<char*>("4224"),
    const_cast<char*>("--verbose"),
    const_cast<char*>("myInputFile")
  };
  market.parseCommandLineArguments(argc, argv);
  ASSERT_FLOAT_EQ(4224, market._seedMoney);
  ASSERT_TRUE(market._verbose);
  ASSERT_STREQ("myInputFile", market._inputFileName);
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, parseCommandLineArgumentsShorthand) {
  MarketSimulator market;
  int argc = 5;
  char* argv[5] = {
    const_cast<char*>("./MarketSimulatorMain"),
    const_cast<char*>("-s"),
    const_cast<char*>("4224"),
    const_cast<char*>("-v"),
    const_cast<char*>("myInputFile")
  };
  market.parseCommandLineArguments(argc, argv);
  ASSERT_FLOAT_EQ(4224, market._seedMoney);
  ASSERT_TRUE(market._verbose);
  ASSERT_STREQ("myInputFile", market._inputFileName);
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, parseCommandLineArgumentsWithNoArguments) {
  MarketSimulator market;
  int argc = 1;
  char* argv[1] = {
    const_cast<char*>("./MarketSimulatorMain")
  };
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(market.parseCommandLineArguments(argc, argv), "Usage: .*");
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, parseCommandLineArgumentsNoFileName) {
  MarketSimulator market;
  int argc = 4;
  char* argv[4] = {
    const_cast<char*>("./MarketSimulatorMain"),
    const_cast<char*>("-s"),
    const_cast<char*>("4224"),
    const_cast<char*>("-v"),
  };
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(market.parseCommandLineArguments(argc, argv), "Usage: .*");
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, parseCommandLineArgumentsOnlyFileName) {
  MarketSimulator market;
  int argc = 2;
  char* argv[2] = {
    const_cast<char*>("./MarketSimulatorMain"),
    const_cast<char*>("myInputFile")
  };
  market.parseCommandLineArguments(argc, argv);
  ASSERT_FLOAT_EQ(1000, market._seedMoney);
  ASSERT_FALSE(market._verbose);
  ASSERT_STREQ("myInputFile", market._inputFileName);
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, simulate) {
  MarketSimulator market;
  Trader trader;
  market._inputFileName = "inputTest.csv";
  market._verbose = false;
  market._seedMoney = 10;

  // Create a test file with some sample input lines.
  FILE* inputFile = fopen(market._inputFileName, "w");
  fprintf(inputFile, "2020-06-19 00:00:00\t0.5\n"
                     "2020-06-19 00:01:00\t0.6\n"
                     "2020-06-19 00:02:00\t1.0\n"
                     "2020-06-19 00:03:00\t2.0\n"
                     "2020-06-19 00:04:00\t0.8\n");
  fclose(inputFile);

  market.simulate(&trader);
  ASSERT_EQ(2, trader._numBitcoins);
  ASSERT_FLOAT_EQ(7, trader._money);

  // Delete the test file.
  unlink(market._inputFileName);
}

// _____________________________________________________________________________
TEST(MarketSimulatorTest, simulateWithNonExistingInputFile) {
  MarketSimulator market;
  Trader trader;
  market._inputFileName = "doesNotExist";
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(market.simulate(&trader), "Error: Could not open input file.*");
}
