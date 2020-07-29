// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <getopt.h>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include "./WordCounter.h"

using std::string;
using std::vector;
using std::pair;

WordCounter::WordCounter() {
  _minLength = 10;
  _inputFileName = "";
  _topK = 15;
  _counterWords = 0;
}

WordCounter::~WordCounter() {
}

void WordCounter::printUsageAndExit() const {
  fprintf(stderr,
    "Usage: ./WordCounterMain [options] <file>\n"
    "\n"
    " --length, -l <arg>: specify the minimum length of a word\n"
    " --top-k, -k <arg>: specify how many top words you want\n");
  exit(1);
}

void WordCounter::parseCommandLineArguments(int argc, char** argv) {
  struct option options[] = {
    { "length", 1, NULL, 'l'},
    { "top-k", 1, NULL, 'k'},
    { NULL, 0, NULL, 0 }
  };
  optind = 1;
  while (true) {
    char c = getopt_long(argc, argv, "l:k:", options, NULL);
    if (c == -1) break;
    switch (c) {
      case 'l':
        _minLength = atoi(optarg);
        break;
      case 'k':
        _topK = atoi(optarg);
        break;
    }
  }
  if (optind >= argc) printUsageAndExit();
  _inputFileName = argv[optind];
}

int WordCounter::getNumWords() const {
  return _counterWords;
}

int WordCounter::getWordCount(const string &s) const {
  try {
    return _words.at(s);
  }
  catch (const std::out_of_range& oor) {}
  return 0;
}

void WordCounter::updateWordCount(const string &s) {
  if (s.length() >= _minLength) {
    if (getWordCount(s) == 0) _counterWords++;
    _words[s]++;
  }
}

string WordCounter::toLowerCase(string s) const {
  size_t c = 0;
  size_t counter = 0;
  for (const auto& i : s) {
    c = size_t(i);
    if (c < 91) s[counter] += 32;
    counter++;
  }
  return s;
}

void WordCounter::processFile() {
  std::ifstream file(_inputFileName);
  if (file.fail()) {
    perror("Error opening file: could not open file");
    exit(1);
  }
  string line;
  while (std::getline(file, line)) {
    size_t start = 0;
    size_t count = 0;
    size_t c = 0;
    size_t end = line.length();
    for (const auto& i : line) {
      c = size_t(i);
      if (!((c > 64 && c < 91) || (c > 96 && c < 123)) || count == end-1) {
        if (count == end-1 && ((c > 64 && c < 91) || (c > 96 && c < 123))) {
          count++;
        }
        if ((start < count) && ((count - start) >= _minLength)) {
          updateWordCount(toLowerCase(line.substr(start, count - start)));
        }
        count++;
        start = count;
      } else {
        count++;
      }
    }
  }
  file.close();
}

vector< pair<string, size_t> > WordCounter::computeMostFrequentWords() const {
  vector< pair<string, size_t> > vtemp;
  for (const auto& p : _words) {
    vtemp.push_back(p);
  }
  std::sort(vtemp.begin(), vtemp.end(),
    [](pair<string, size_t>& x, pair<string, size_t>& y) {
      return x.second > y.second; });
  size_t counter = 0;
  vector< pair<string, size_t> > v;
  for (const auto& p : vtemp) {
    counter++;
    if (counter > _topK) break;
    v.push_back(p);
  }
  return v;
}
