// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <string>
#include <vector>
#include <iostream>
#include "./Wikidata.h"

using std::string;
using std::vector;

int main(int argc, char** argv) {
  Wikidata wiki;
  wiki.parseCommandLineArguments(argc, argv);
  wiki.readFile(wiki._inputFileName);
  string subString = "";
  while (true) {
    std::cout << "\nGeben Sie einen Suchparameter ein.\n";
    std::cin >> subString;
    std::cout << "\n";
    vector<string> v = wiki.search(subString);
    size_t end = 10;
    if (v.size() < 10) end = v.size();
    if (end == 0) std::cout << "Keine Treffer.\n";
    for (size_t i = 0; i < end; i++) {
    std::cout << i+1 << "\t" << v[i] << "\n";
    }
  }
}
