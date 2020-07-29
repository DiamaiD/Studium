// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef SET_H_
#define SET_H_

#include <gtest/gtest.h>

template <class T>
class Set {
 public:
  // Create an empty Set of size 0
  Set();

  // Destructor
  ~Set();

  // return true if <T> is in the array, otherwise false
  bool lookup(const T element) const;

  // insert <T> in the array
  void insert(const T element);

  // remove <T> from the array
  void erase(const T element);

 private:
  // array of elements of type <T>
  T* _elements;

  // The number of elements.
  int _size;

  // the real size of the array
  int _actualSize;

  // if number of elements is the same as the size of the array
  // resize the array with the factor 2
  void resize();

  FRIEND_TEST(SetTest, insertAndEraseAndLookup);
};

template <>
class Set<unsigned char> {
 public:
  // Create the boolean array of 256 bools
  Set();

  // Destructor
  ~Set();

  // return true if char is in the array, otherwise false
  bool lookup(const unsigned char element) const;

  // set the corresponding boolean value to 1
  void insert(const unsigned char element);

  // set the corresponding boolean value to 0
  void erase(const unsigned char element);

 private:
  // The elements of the array as boolean values
  // for example if _elements[80] == True then the Char 'P' is
  // in the array
  bool* _elements;

  // The number of elements.
  int _size;

  FRIEND_TEST(SetCharTest, insertAndEraseAndLookup);
};

#endif  // SET_H_
