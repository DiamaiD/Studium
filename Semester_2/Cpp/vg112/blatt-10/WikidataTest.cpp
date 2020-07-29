// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <string>
#include "./Wikidata.h"
#include "./Entity.h"

// ____________________________________________________________________________
TEST(WikidataTest, readInvalidFile) {
  Wikidata wd;
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ASSERT_DEATH(wd.readFile(std::string("InvalidFile")), "Error .*");
}

// ____________________________________________________________________________
TEST(WikidataTest, readFileAndSearch) {
  Wikidata wd;
  ASSERT_EQ(0, wd._entities.size());
  wd.readFile(std::string("WikidataTest.testfile"));
  ASSERT_EQ(9, wd._entities.size());
  wd.readFile(std::string("WikidataTest.testfile"));
  ASSERT_EQ(9, wd._entities.size());

  {
    auto res = wd.search("isNotContainedInFile");
    ASSERT_EQ(0, res.size());
  }
  {
    auto res = wd.search("broken line here");
    ASSERT_EQ(0, res.size());
  }
  {
    auto res = wd.search("E");
    ASSERT_EQ(5, res.size());
    ASSERT_STREQ("Christopher Lee place of birth: Belgravia", res[0].c_str());
    ASSERT_STREQ("Metallica", res[1].c_str());
    ASSERT_STREQ("Iron Maiden", res[2].c_str());
    ASSERT_STREQ("Rhapsody of Fire", res[3].c_str());
    ASSERT_STREQ("Iron Maiden: Flight 666 cast member: Iron Maiden",
                 res[4].c_str());
  }
  {
    auto res = wd.search("eE");
    ASSERT_EQ(1, res.size());
    ASSERT_STREQ("Christopher Lee place of birth: Belgravia", res[0].c_str());
  }
  {
    auto res = wd.search("T");
    ASSERT_EQ(5, res.size());
    ASSERT_STREQ("Christopher Lee place of birth: Belgravia", res[0].c_str());
    ASSERT_STREQ("Metallica", res[1].c_str());
    ASSERT_STREQ("Nightwish", res[2].c_str());
    ASSERT_STREQ("Black Sabbath", res[3].c_str());
    ASSERT_STREQ("Iron Maiden: Flight 666 cast member: Iron Maiden",
                 res[4].c_str());
  }
  {
    auto res = wd.search("ck");
    ASSERT_EQ(2, res.size());
    ASSERT_STREQ("Black Sabbath", res[0].c_str());
    ASSERT_STREQ("Jack Black place of birth: Hermosa Beach", res[1].c_str());
  }
}
