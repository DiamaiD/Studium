// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef WORDCOUNTER_H_
#define WORDCOUNTER_H_

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::string;
using std::unordered_map;

class WordCounter {
 public:
  WordCounter();
  ~WordCounter();

  void parseCommandLineArguments(int argc, char** argv);

  void processFile();

  int getNumWords() const;

  int getWordCount(const string &s) const;

  vector< pair<string, size_t> > computeMostFrequentWords() const;

 private:
  int _minLength;

  const char* _inputFileName;

  int _counterWords;

  unordered_map<string, int> _words;

  int _topK;

  void printUsageAndExit() const;

  string toLowerCase(string s) const;

  void updateWordCount(const string &s);

  FRIEND_TEST(WordCounter, constructor);
  FRIEND_TEST(WordCounter, printUsageAndExit);
  FRIEND_TEST(WordCounter, parseCommandLineArguments);
  FRIEND_TEST(WordCounter, parseCommandLineArgumentsShortHand);
  FRIEND_TEST(WordCounter, parseCommandLineArgumentsWithNoArguments);
  FRIEND_TEST(WordCounter, parseCommandLineArgumentsNoFileName);
  FRIEND_TEST(WordCounter, parseCommandLineArgumentsOnlyFileName);
  FRIEND_TEST(WordCounter, processFile);
  FRIEND_TEST(WordCounter, processNonExistingFile);
  FRIEND_TEST(WordCounter, updateWordCount);
  FRIEND_TEST(WordCounter, computeMostFrequentWords);
  FRIEND_TEST(WordCounter, getNumWordsAndGetWordCount);
};

#endif  // WORDCOUNTER_H_
