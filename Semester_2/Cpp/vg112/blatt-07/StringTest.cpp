// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <gtest/gtest.h>
#include <stdio.h>
#include "./String.h"

// _____________________________________________________________________________
TEST(StringTest, constructor) {
  String s;
  ASSERT_EQ(0, s._length);
  ASSERT_EQ(0, s._contents[0]);
}

// _____________________________________________________________________________
TEST(StringTest, copyConstructor) {
    String s;
    s.set("Bloed");
    String r(s);
    r._contents[0] = 'F';

    // Assert that the pointers s._contents and r._contents are *not* equal.
    ASSERT_NE(s._contents, r._contents);

    ASSERT_EQ(5, s._length);
    ASSERT_EQ('B', s._contents[0]);
    ASSERT_EQ('l', s._contents[1]);
    ASSERT_EQ('o', s._contents[2]);
    ASSERT_EQ('e', s._contents[3]);
    ASSERT_EQ('d', s._contents[4]);
    ASSERT_EQ(0, s._contents[5]);

    ASSERT_EQ(5, r._length);
    ASSERT_EQ('F', r._contents[0]);
    ASSERT_EQ('l', r._contents[1]);
    ASSERT_EQ('o', r._contents[2]);
    ASSERT_EQ('e', r._contents[3]);
    ASSERT_EQ('d', r._contents[4]);
    ASSERT_EQ(0, r._contents[5]);
}

// _____________________________________________________________________________
TEST(StringTest, set) {
    String s;
    s.set("Doof");
    ASSERT_EQ(4, s._length);
    ASSERT_EQ('D', s._contents[0]);
    ASSERT_EQ('o', s._contents[1]);
    ASSERT_EQ('o', s._contents[2]);
    ASSERT_EQ('f', s._contents[3]);
    ASSERT_EQ(0, s._contents[4]);
}

// _____________________________________________________________________________
TEST(StringTest, toFloat) {
    String s;
    s.set("");
    ASSERT_FLOAT_EQ(0.0, s.toFloat());
    s.set("1");
    ASSERT_FLOAT_EQ(1.0, s.toFloat());
    s.set("3.14");
    ASSERT_FLOAT_EQ(3.14, s.toFloat());
    s.set("-3.14");
    ASSERT_FLOAT_EQ(-3.14, s.toFloat());
    s.set("3.14\n");
    ASSERT_FLOAT_EQ(3.14, s.toFloat());
    s.set("doof");
    ASSERT_FLOAT_EQ(0.0, s.toFloat());
}

// _____________________________________________________________________________
TEST(StringTest, split) {
    String s;
    StringArray result;
    s.set("this;is;a;test");
    s.split(';', &result);

    ASSERT_EQ(4, result.size());

    String str0 = result.get(0);
    ASSERT_EQ(4, str0._length);
    ASSERT_EQ('t', str0._contents[0]);
    ASSERT_EQ('h', str0._contents[1]);
    ASSERT_EQ('i', str0._contents[2]);
    ASSERT_EQ('s', str0._contents[3]);
    ASSERT_EQ(0, str0._contents[4]);

    String str1 = result.get(1);
    ASSERT_EQ(2, str1._length);
    ASSERT_EQ('i', str1._contents[0]);
    ASSERT_EQ('s', str1._contents[1]);
    ASSERT_EQ(0, str1._contents[2]);

    String str2 = result.get(2);
    ASSERT_EQ(1, str2._length);
    ASSERT_EQ('a', str2._contents[0]);
    ASSERT_EQ(0, str2._contents[1]);

    String str3 = result.get(3);
    ASSERT_EQ(4, str3._length);
    ASSERT_EQ('t', str3._contents[0]);
    ASSERT_EQ('e', str3._contents[1]);
    ASSERT_EQ('s', str3._contents[2]);
    ASSERT_EQ('t', str3._contents[3]);
    ASSERT_EQ(0, str3._contents[4]);
}

// _____________________________________________________________________________
TEST(StringTest, splitEmptyString) {
    String s;
    StringArray result;
    s.set("");
    s.split(';', &result);

    ASSERT_EQ(1, result.size());

    String str0 = result.get(0);
    ASSERT_EQ(0, str0._length);
    ASSERT_EQ(0, str0._contents[0]);
}

// _____________________________________________________________________________
TEST(StringTest, splitDelimiterAtStart) {
    String s;
    StringArray result;
    s.set(";test");
    s.split(';', &result);

    ASSERT_EQ(2, result.size());

    String str0 = result.get(0);
    ASSERT_EQ(0, str0._length);
    ASSERT_EQ(0, str0._contents[0]);

    String str1 = result.get(1);
    ASSERT_EQ(4, str1._length);
    ASSERT_EQ('t', str1._contents[0]);
    ASSERT_EQ('e', str1._contents[1]);
    ASSERT_EQ('s', str1._contents[2]);
    ASSERT_EQ('t', str1._contents[3]);
    ASSERT_EQ(0, str1._contents[4]);
}

// _____________________________________________________________________________
TEST(StringTest, splitDelimiterAtEnd) {
    String s;
    StringArray result;
    s.set("test;");
    s.split(';', &result);

    ASSERT_EQ(2, result.size());

    String str0 = result.get(0);
    ASSERT_EQ(4, str0._length);
    ASSERT_EQ('t', str0._contents[0]);
    ASSERT_EQ('e', str0._contents[1]);
    ASSERT_EQ('s', str0._contents[2]);
    ASSERT_EQ('t', str0._contents[3]);
    ASSERT_EQ(0, str0._contents[4]);

    String str1 = result.get(1);
    ASSERT_EQ(0, str1._length);
    ASSERT_EQ(0, str1._contents[0]);
}

// _____________________________________________________________________________
TEST(StringTest, splitNoDelimiter) {
    String s;
    StringArray result;
    s.set("this!is!a!test");
    s.split(';', &result);

    ASSERT_EQ(1, result.size());

    String str0 = result.get(0);
    ASSERT_EQ(14, str0._length);
    ASSERT_EQ('t', str0._contents[0]);
    ASSERT_EQ('h', str0._contents[1]);
    ASSERT_EQ('i', str0._contents[2]);
    ASSERT_EQ('s', str0._contents[3]);
    ASSERT_EQ('!', str0._contents[4]);
    ASSERT_EQ('i', str0._contents[5]);
    ASSERT_EQ('s', str0._contents[6]);
    ASSERT_EQ('!', str0._contents[7]);
    ASSERT_EQ('a', str0._contents[8]);
    ASSERT_EQ('!', str0._contents[9]);
    ASSERT_EQ('t', str0._contents[10]);
    ASSERT_EQ('e', str0._contents[11]);
    ASSERT_EQ('s', str0._contents[12]);
    ASSERT_EQ('t', str0._contents[13]);
    ASSERT_EQ(0, str0._contents[14]);
}

// ============================================================================
// StringArray.

// _____________________________________________________________________________
TEST(StringArrayTest, constructor) {
    StringArray sa;
    ASSERT_EQ(0, sa._size);
    ASSERT_EQ(0, sa._contents);
}

// _____________________________________________________________________________
TEST(StringArrayTest, setSize) {
    StringArray sa;
    sa.setSize(4);
    ASSERT_EQ(4, sa._size);
}

// _____________________________________________________________________________
TEST(StringArrayTest, set) {
    StringArray array;
    array.setSize(2);

    String s0;
    s0.set("Doof");
    array.set(0, s0);

    String s1;
    s1.set("Bloed");
    array.set(1, s1);

    ASSERT_EQ(2, array._size);

    String sa0 = array._contents[0];
    ASSERT_EQ(4, sa0._length);
    ASSERT_EQ('D', sa0._contents[0]);
    ASSERT_EQ('o', sa0._contents[1]);
    ASSERT_EQ('o', sa0._contents[2]);
    ASSERT_EQ('f', sa0._contents[3]);
    ASSERT_EQ(0, sa0._contents[4]);

    String sa1 = array._contents[1];
    ASSERT_EQ(5, sa1._length);
    ASSERT_EQ('B', sa1._contents[0]);
    ASSERT_EQ('l', sa1._contents[1]);
    ASSERT_EQ('o', sa1._contents[2]);
    ASSERT_EQ('e', sa1._contents[3]);
    ASSERT_EQ('d', sa1._contents[4]);
    ASSERT_EQ(0, sa1._contents[5]);
}

// _____________________________________________________________________________
TEST(StringArrayTest, get) {
    StringArray array;
    array.setSize(2);

    String s0;
    s0.set("Doof");
    array.set(0, s0);

    String s1;
    s1.set("Bloed");
    array.set(1, s1);

    ASSERT_EQ(2, array._size);

    String sa0 = array.get(0);
    ASSERT_EQ(4, sa0._length);
    ASSERT_EQ('D', sa0._contents[0]);
    ASSERT_EQ('o', sa0._contents[1]);
    ASSERT_EQ('o', sa0._contents[2]);
    ASSERT_EQ('f', sa0._contents[3]);
    ASSERT_EQ(0, sa0._contents[4]);

    String sa1 = array.get(1);
    ASSERT_EQ(5, sa1._length);
    ASSERT_EQ('B', sa1._contents[0]);
    ASSERT_EQ('l', sa1._contents[1]);
    ASSERT_EQ('o', sa1._contents[2]);
    ASSERT_EQ('e', sa1._contents[3]);
    ASSERT_EQ('d', sa1._contents[4]);
    ASSERT_EQ(0, sa1._contents[5]);
}
