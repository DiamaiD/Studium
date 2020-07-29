// Copyright 2020, University of Freiburg,
// Authors: Hannah Bast <bast@cs.uni-freiburg.de>,
//          Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//          Johanna Götz <johanna.goetz@uranus.uni-freiburg.de>,
//          Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>
#include "./WordCounter.h"

// _____________________________________________________________________________
TEST(WordCounter, constructor) {
  WordCounter wc;
  ASSERT_STREQ("", wc._inputFileName);
  ASSERT_EQ(10, wc._minLength);
  ASSERT_EQ(15, wc._topK);
}

// _____________________________________________________________________________
TEST(WordCounter, printUsageAndExit) {
  WordCounter wc;
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(wc.printUsageAndExit(), "Usage: ./WordCounterMain .*");
}

// _____________________________________________________________________________
TEST(WordCounter, parseCommandLineArguments) {
  WordCounter wc;
  int argc = 6;
  char* argv[6] = {
    const_cast<char*>("./WordCounterMain"),
    const_cast<char*>("--length"),
    const_cast<char*>("7"),
    const_cast<char*>("--top-k"),
    const_cast<char*>("12"),
    const_cast<char*>("Big-Lebowski,-The.txt")
  };
  wc.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(7, wc._minLength);
  ASSERT_EQ(12, wc._topK);
  ASSERT_EQ("Big-Lebowski,-The.txt", wc._inputFileName);
}

// _____________________________________________________________________________
TEST(WordCounter, parseCommandLineArgumentsShortHand) {
  WordCounter wc;
  int argc = 6;
  char* argv[6] = {
    const_cast<char*>("./WordCounterMain"),
    const_cast<char*>("-l"),
    const_cast<char*>("4"),
    const_cast<char*>("-k"),
    const_cast<char*>("17"),
    const_cast<char*>("Big-Lebowski,-The.txt")
  };
  wc.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(4, wc._minLength);
  ASSERT_EQ(17, wc._topK);
  ASSERT_EQ("Big-Lebowski,-The.txt", wc._inputFileName);
}

// _____________________________________________________________________________
TEST(WordCounter, parseCommandLineArgumentsWithNoArguments) {
  WordCounter wc;
  int argc = 1;
  char* argv[1] = {
    const_cast<char*>("./WordCounterMain")
  };
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(wc.parseCommandLineArguments(argc, argv), "Usage: .*");
}

// _____________________________________________________________________________
TEST(WordCounter, parseCommandLineArgumentsNoFileName) {
  WordCounter wc;
  int argc = 5;
  char* argv[5] = {
    const_cast<char*>("./WordCounterMain"),
    const_cast<char*>("--length"),
    const_cast<char*>("7"),
    const_cast<char*>("-top-k"),
    const_cast<char*>("12")
  };
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(wc.parseCommandLineArguments(argc, argv), "Usage: .*");
}

// _____________________________________________________________________________
TEST(WordCounter, parseCommandLineArgumentsOnlyFileName) {
  WordCounter wc;
  int argc = 2;
  char* argv[2] = {
    const_cast<char*>("./WordCounterMain"),
    const_cast<char*>("Big-Lebowski,-The.txt")
  };
  wc.parseCommandLineArguments(argc, argv);
  ASSERT_EQ(10, wc._minLength);
  ASSERT_EQ(15, wc._topK);
  ASSERT_EQ("Big-Lebowski,-The.txt", wc._inputFileName);
}

// _____________________________________________________________________________
TEST(WordCounter, processFile) {
  FILE* input = fopen("WordCounterTest.tmp", "w");
  fprintf(input, "Doof123bloed Bloed DOOF !doof! (extra) doof,\n"
                 "bloed dooof  the456   doof+bloed\n");
  fclose(input);

  WordCounter wc;
  // Set min length to 4 to allow shorter example words in the tests.
  wc._minLength = 4;

  ASSERT_EQ(0, wc.getNumWords());

  wc._inputFileName = "WordCounterTest.tmp";
  wc.processFile();
  ASSERT_EQ(4, wc.getNumWords());
  ASSERT_EQ(5, wc.getWordCount("doof"));
  ASSERT_EQ(4, wc.getWordCount("bloed"));
  ASSERT_EQ(1, wc.getWordCount("extra"));
  ASSERT_EQ(1, wc.getWordCount("dooof"));
  ASSERT_EQ(0, wc.getWordCount("the"));

  wc.processFile();
  ASSERT_EQ(4, wc.getNumWords());
  ASSERT_EQ(10, wc.getWordCount("doof"));
  ASSERT_EQ(8, wc.getWordCount("bloed"));
  ASSERT_EQ(2, wc.getWordCount("extra"));
  ASSERT_EQ(2, wc.getWordCount("dooof"));
  ASSERT_EQ(0, wc.getWordCount("the"));

  unlink("WordCounterTest.tmp");
}

// _____________________________________________________________________________
TEST(WordCounter, processNonExistingFile) {
  WordCounter wc;
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  wc._inputFileName = "nonExistingFile";
  ASSERT_DEATH(wc.processFile(),
               "Error opening file: .*");
}

// _____________________________________________________________________________
TEST(WordCounter, updateWordCount) {
  WordCounter wc;
  // Set min length to 5 to allow shorter example words in the tests.
  wc._minLength = 5;

  ASSERT_EQ(0, wc.getNumWords());

  std::string word = "";
  wc.updateWordCount(word);
  ASSERT_EQ(0, wc.getNumWords());

  word = "the";
  wc.updateWordCount(word);
  word = "doof";
  wc.updateWordCount(word);
  word = "bloed";
  wc.updateWordCount(word);
  ASSERT_EQ(1, wc.getNumWords());
  ASSERT_EQ(0, wc.getWordCount("the"));
  ASSERT_EQ(0, wc.getWordCount("doof"));
  ASSERT_EQ(1, wc.getWordCount("bloed"));

  word = "doof";
  wc.updateWordCount(word);
  word = "bloed";
  wc.updateWordCount(word);
  word = "bloed";
  wc.updateWordCount(word);
  word = "saubloed";
  wc.updateWordCount(word);
  ASSERT_EQ(2, wc.getNumWords());
  ASSERT_EQ(0, wc.getWordCount("doof"));
  ASSERT_EQ(3, wc.getWordCount("bloed"));
  ASSERT_EQ(1, wc.getWordCount("saubloed"));

  word = "freiburg";
  wc.updateWordCount(word);
  word = "dreisam";
  wc.updateWordCount(word);
  word = "schwarzwald";
  wc.updateWordCount(word);
  word = "breisgau";
  wc.updateWordCount(word);
  ASSERT_EQ(6, wc.getNumWords());
  ASSERT_EQ(0, wc.getWordCount("doof"));
  ASSERT_EQ(3, wc.getWordCount("bloed"));
  ASSERT_EQ(1, wc.getWordCount("freiburg"));
  ASSERT_EQ(1, wc.getWordCount("dreisam"));
  ASSERT_EQ(1, wc.getWordCount("schwarzwald"));
  ASSERT_EQ(1, wc.getWordCount("breisgau"));
  ASSERT_EQ(0, wc.getWordCount("stuttgart"));
}

// _____________________________________________________________________________
TEST(WordCounter, computeMostFrequentWords) {
  WordCounter wc;
  // Set min length to 4 to allow shorter example words in the tests
  wc._minLength = 4;

  ASSERT_EQ(0, wc.getNumWords());

  std::vector<std::pair<std::string, size_t> > result;

  result = wc.computeMostFrequentWords();
  ASSERT_EQ(0, result.size());

  std::string word;
  word = "doof";
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  word = "bloed";
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  word = "saubloed";
  wc.updateWordCount(word);
  wc.updateWordCount(word);
  wc.updateWordCount(word);

  // Set the number of results to 1.
  wc._topK = 1;
  result = wc.computeMostFrequentWords();
  ASSERT_EQ(1, result.size());
  ASSERT_STREQ("doof", result[0].first.c_str());
  ASSERT_EQ(5, result[0].second);

  // Set the number of results to 3.
  wc._topK = 3;
  result = wc.computeMostFrequentWords();
  ASSERT_EQ(3, result.size());
  ASSERT_STREQ("doof", result[0].first.c_str());
  ASSERT_EQ(5, result[0].second);
  ASSERT_STREQ("saubloed", result[1].first.c_str());
  ASSERT_EQ(3, result[1].second);
  ASSERT_STREQ("bloed", result[2].first.c_str());
  ASSERT_EQ(2, result[2].second);

  // Set the number of results to 100.
  wc._topK = 100;
  result = wc.computeMostFrequentWords();
  ASSERT_EQ(3, result.size());
  ASSERT_STREQ("doof", result[0].first.c_str());
  ASSERT_EQ(5, result[0].second);
  ASSERT_STREQ("saubloed", result[1].first.c_str());
  ASSERT_EQ(3, result[1].second);
  ASSERT_STREQ("bloed", result[2].first.c_str());
  ASSERT_EQ(2, result[2].second);
}

// _____________________________________________________________________________
TEST(WordCounter, getNumWordsAndGetWordCount) {
  WordCounter wc;
  // Assert that a string that is not contained in the counter before calling
  // getWordCount() is also not contained *after* calling the method.
  ASSERT_EQ(0, wc.getNumWords());
  ASSERT_EQ(0, wc.getWordCount("doof"));
  ASSERT_EQ(0, wc.getNumWords());
  ASSERT_EQ(0, wc.getWordCount("bloed"));
  ASSERT_EQ(0, wc.getNumWords());
}
