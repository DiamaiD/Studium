// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Hannah Bast <bast@cs.uni-freiburg.de>,
//          Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//          Johanna Götz <johanna.goetz@uranus.uni-freiburg.de>,
//          Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "./WordCounter.h"

// _____________________________________________________________________________
int main(int argc, char** argv) {
  WordCounter wc;
  // Parse the command line arguments (filename, length and top-k).
  wc.parseCommandLineArguments(argc, argv);
  // Read the file specified via the command line args and count the words.
  wc.processFile();
  // Compute the most frequent words.
  std::vector<std::pair<std::string, size_t>> pairs =
      wc.computeMostFrequentWords();
  // Output the most frequent words.
  for (size_t i = 0; i < pairs.size(); i++) {
    std::cout << (i + 1) << ". " << pairs[i].first.c_str();
    std::cout << " (" << pairs[i].second << ")" << std::endl;
  }
}
