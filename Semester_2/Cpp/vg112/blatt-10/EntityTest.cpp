// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "./Entity.h"

// ____________________________________________________________________________
// Data used by all tests.
std::vector<std::string> triple1 {"Demo Entity", "place of birth", "C++"};
std::vector<std::string> triple2 {"Demo Entity", "cast member", "1"};
std::vector<std::string> triple3 {"Demo Entity", "cast member", "2"};
std::vector<std::string> triple4 {"Demo Entity", "cast member", "3"};

// ____________________________________________________________________________
TEST(EntityTest, blackbox) {
  {
    Entity entity("Demo Entity");
    ASSERT_STREQ("Demo Entity", entity.toString().c_str());
  }
  {
    Entity entity("Demo Entity");
    entity.addTriple(triple1);
    entity.addTriple(triple2);
    entity.addTriple(triple3);
    entity.addTriple(triple4);
    ASSERT_STREQ("Demo Entity", entity.toString().c_str());
  }
}

// ____________________________________________________________________________
TEST(PersonTest, blackbox) {
  {
    Person entity("Demo Entity");
    ASSERT_STREQ("Demo Entity", entity.toString().c_str());
  }
  {
    Person entity("Demo Entity");
    entity.addTriple(triple1);
    entity.addTriple(triple2);
    entity.addTriple(triple3);
    entity.addTriple(triple4);
    ASSERT_STREQ("Demo Entity place of birth: C++", entity.toString().c_str());
  }
}

// ____________________________________________________________________________
TEST(FilmTest, blackbox) {
  {
    Film entity("Demo Entity");
    ASSERT_STREQ("Demo Entity", entity.toString().c_str());
  }
  {
    Film entity("Demo Entity");
    entity.addTriple(triple1);
    entity.addTriple(triple2);
    entity.addTriple(triple3);
    entity.addTriple(triple4);
    ASSERT_STREQ("Demo Entity cast member: 1, 2, 3", entity.toString().c_str());
  }
}
