// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef WIKIDATA_H_
#define WIKIDATA_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "./Entity.h"

using std::string;
using std::vector;

class Wikidata {
 public:
  Wikidata();
  ~Wikidata();

  void readFile(const string& filename);

  vector<string> search(string s) const;

  void parseCommandLineArguments(int argc, char** argv);

  string _inputFileName;

 private:
  vector<Entity*> _entities;

  void printUsageAndExit() const;

  FRIEND_TEST(WikidataTest, readInvalidFile);
  FRIEND_TEST(WikidataTest, readFileAndSearch);
};

#endif  // WIKIDATA_H_
