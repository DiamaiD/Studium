// Copyright 2020, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//          Claudius Korzen <korzen@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Set.h"

// _____________________________________________________________________________
TEST(SetCharTest, insertAndEraseAndLookup) {
  Set<unsigned char> set;

  // Test if the set is empty:
  // Assert that each character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(0, set._size);

  // Insert element 'a'.
  set.insert('a');
  // Assert that 'a' is found.
  ASSERT_TRUE(set.lookup('a'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'a') { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(1, set._size);

  // Insert element 'a' again. This should result in no change.
  set.insert('a');
  // Assert that 'a' is found.
  ASSERT_TRUE(set.lookup('a'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'a') { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(1, set._size);

  // Insert element 'b'.
  set.insert('b');
  // Assert that 'a' and 'b' is found.
  ASSERT_TRUE(set.lookup('a'));
  ASSERT_TRUE(set.lookup('b'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'a') { continue; }
    if (c == 'b') { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(2, set._size);

  // Insert element 'ü' (hex: \xfc, dec: 252).
  set.insert('\xfc');
  // Assert that 'a', 'b' and 'ü' is found.
  ASSERT_TRUE(set.lookup('a'));
  ASSERT_TRUE(set.lookup('b'));
  ASSERT_TRUE(set.lookup('\xfc'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'a') { continue; }
    if (c == 'b') { continue; }
    if (c == 252) { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(3, set._size);

  // Erase element 'a'.
  set.erase('a');
  // Assert that 'b' and 'ü' is found.
  ASSERT_TRUE(set.lookup('b'));
  ASSERT_TRUE(set.lookup('\xfc'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'b') { continue; }
    if (c == 252) { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(2, set._size);

  // Erase element 'a' again. This should result in no change.
  set.erase('a');
  // Assert that 'b' and 'ü' is found.
  ASSERT_TRUE(set.lookup('b'));
  ASSERT_TRUE(set.lookup('\xfc'));
  // Assert that each other character is *not* found.
  for (int i = 0; i < 256; i++) {
    unsigned char c = (unsigned char) i;
    if (c == 'b') { continue; }
    if (c == 252) { continue; }
    ASSERT_FALSE(set.lookup(c)) << "Failed for " << c << " (dec: " << i << ")";
  }
  ASSERT_EQ(2, set._size);
}
