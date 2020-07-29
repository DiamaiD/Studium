// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef STRING_H_
#define STRING_H_

#include <gtest/gtest.h>

class StringArray;

// A simple String class, for demonstration purposes in the lecture and as a
// basis for Ü6.
class String {
 private:
    // The contents of the string (including the trailing 0).
    char* _contents;

    // The length of the string (size_t is an unsigned integer with the right
    // size for the machine).
    size_t _length;

    // ID of the object (1, 2, 3, ...)
    int _objectId;

    // Number of objects created (by whatever constructor).
    static int _numObjects;

    bool checkAllowedFloatChars(const char s) const;

    String getPart(const unsigned start, const unsigned end) const;

 public:
    // Create an empty string (default constructor).
    String();

    void split(const char d, StringArray* strArray) const;

    // Deep copy of given object (copy constructor).
    String(const String& s);

    // Move the contents of the given object to this object (move constructor).
    String(String&& s);

    // When the object goes out of scope, free the memory (destructor).
    ~String();

    // The length of the string.
    size_t size() const;

    void setSize(const unsigned n);

    // Set to given C-style (null-terminated) string.
    void set(const char* s);

    char* get() const;

    // Return a reversed version of the string.
    String reversed() const;

    // Convert String to float
    float toFloat();

    FRIEND_TEST(StringTest, constructor);
    FRIEND_TEST(StringTest, copyConstructor);
    FRIEND_TEST(StringTest, set);
    FRIEND_TEST(StringTest, toFloat);
    FRIEND_TEST(StringTest, split);
    FRIEND_TEST(StringTest, splitEmptyString);
    FRIEND_TEST(StringTest, splitDelimiterAtStart);
    FRIEND_TEST(StringTest, splitDelimiterAtEnd);
    FRIEND_TEST(StringTest, splitNoDelimiter);
    FRIEND_TEST(StringArrayTest, get);
    FRIEND_TEST(StringArrayTest, set);
};

class StringArray {
 private:
    // The contents of the stringArray.
    String* _contents;

    // The length of the stringArray
    size_t _size;

 public:
    // Create an empty stringArray (default constructor).
    StringArray();

    // When the object goes out of scope, free the memory (destructor).
    ~StringArray();

    // The size of the stringArray.
    size_t size() const;

    void setSize(const unsigned n);

    void set(const unsigned position, String str);

    String get(const unsigned position) const;

    FRIEND_TEST(StringArrayTest, constructor);
    FRIEND_TEST(StringArrayTest, setSize);
    FRIEND_TEST(StringArrayTest, get);
    FRIEND_TEST(StringArrayTest, set);
};

#endif  // STRING_H_
