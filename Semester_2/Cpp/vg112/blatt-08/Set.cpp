// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include "./Set.h"

// ________________________________________________________________________
template <class T>
Set<T>::Set() {
  _elements = 0;
  _size = 0;
  _actualSize = 0;
}

// ________________________________________________________________________
template <class T>
Set<T>::~Set() {
  delete[] _elements;
}

// ________________________________________________________________________
template <class T>
bool Set<T>::lookup(T element) const {
  for (size_t i = 0; i < _size; i++) {
    if (_elements[i] == element) return true;
  }
  return false;
}

// ________________________________________________________________________
template <class T>
void Set<T>::insert(const T element) {
  if (!lookup(element)) {
    if (_size == _actualSize) resize();
    _elements[_size] = element;
    _size++;
  }
}

// ________________________________________________________________________
template <class T>
void Set<T>::resize() {
  if (_size == 0) {
    delete[] _elements;
    _actualSize = 10;
    _elements = new T[_actualSize];
    for (size_t i = 0; i < _actualSize; i++) _elements[i] = 0;
  } else {
    _actualSize *= 2;
    T* newArray = new T[_actualSize];
    for (size_t i = 0; i < _size; i++) newArray[i] = _elements[i];
    delete[] _elements;
    _elements = newArray;
    for (size_t i = _size; i < _actualSize; i++) _elements[i] = 0;
  }
}

// ________________________________________________________________________
template <class T>
void Set<T>::erase(const T element) {
  bool isIn = false;
  int index = 0;
  for (int i = 0; i < _size; i++) {
    if (_elements[i] == element) {
      index = i;
      isIn = true;
      break;
    }
  }
  if (isIn) {
    for (int i = index; i < _size-1; i++) {
      _elements[i] = _elements[i+1];
    }
    _size--;
  }
}

// Explicit instantiation of Set<T> for int and float.
template class Set<int>;
template class Set<float>;

// ________________________________________________________________________
Set<unsigned char>::Set() {
  _elements = new bool[256];
  for (size_t i = 0; i < 256; i++) _elements[i] = 0;
  _size = 0;
}

// ________________________________________________________________________
Set<unsigned char>::~Set() {
  delete[] _elements;
}

// ________________________________________________________________________
bool Set<unsigned char>::lookup(const unsigned char element) const {
  if (_elements[element]) return true;
  return false;
}

// ________________________________________________________________________
void Set<unsigned char>::insert(const unsigned char element) {
  if (!lookup(element)) {
    _elements[element] = 1;
    _size++;
  }
}

// ________________________________________________________________________
void Set<unsigned char>::erase(const unsigned char element) {
  if (lookup(element)) {
    _elements[element] = 0;
    _size--;
  }
}
