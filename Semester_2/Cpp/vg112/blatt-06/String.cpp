// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <string.h>
#include <stdio.h>
#include "./String.h"

// Initialize object count for String class.
int String::_numObjects = 0;
const char allowedFloatChars[] = {'0', '1', '2', '3', '4', '5',
'6', '7', '8', '9', '-', '.'};

// ___________________________________________________________________________
String::String() {
    _contents = new char[1];
    _contents[0] = 0;
    _length = 0;
    _numObjects++;
    _objectId = _numObjects;
    // printf("Created object #%d (default constructor)\n", _objectId);
}

// ___________________________________________________________________________
StringArray::StringArray() {
    _contents = 0;
    _size = 0;
}

// ___________________________________________________________________________
StringArray::~StringArray() {
    delete[] _contents;
}

// ___________________________________________________________________________
String::String(const String& s) {
    _length = s._length;
    _contents = new char[_length + 1];
    for (size_t i = 0; i <= _length; i++) _contents[i] = s._contents[i];
    _numObjects++;
    _objectId = _numObjects;
    // printf("Created object #%d (copy constructor)\n", _objectId);
}

// ___________________________________________________________________________
String::String(String&& s) {
    _length = s._length;
    _contents = s._contents;
    s._contents = 0;
    s._length = 0;
    _numObjects++;
    _objectId = _numObjects;
    // printf("Created object #%d (move constructor)\n", _objectId);
}

// ___________________________________________________________________________
String::~String() {
    delete[] _contents;
    // printf("Bye bye object #%d (destructor)\n", _objectId);
}

// ___________________________________________________________________________
size_t String::size() const {
    return _length;
}

// ___________________________________________________________________________
size_t StringArray::size() const {
    return _size;
}

void String::setSize(const unsigned n) {
    delete[] _contents;
    _contents = new char[n+1];
    for (size_t i = 0; i <= n; i++) _contents[i] = 0;
    _length = n;
}

void StringArray::setSize(const unsigned n) {
    delete[] _contents;
    _contents = new String[n];
    for (size_t i = 0; i < n; i++) {
        _contents[i].setSize(0);
    }
    _size = n;
}

// ___________________________________________________________________________
void String::set(const char* s) {
    size_t n = strlen(s);
    delete[] _contents;
    _contents = new char[n + 1];
    for (size_t i = 0; i <= n; i++) _contents[i] = s[i];
    _length = n;
}

void StringArray::set(const unsigned position, const String str) {
    _contents[position].set(str.get());
}

char* String::get() const {
    return _contents;
}

String StringArray::get(const unsigned position) const {
    return _contents[position];
}

// ___________________________________________________________________________
String String::reversed() const {
    String result;
    result._length = _length;
    result._contents = new char[_length + 1];
    for (size_t i = 0; i < _length; i++)
    result._contents[i] = _contents[_length - 1 - i];
    result._contents[_length] = 0;
    return result;
}

float String::toFloat() {
    if (_contents == "") {
        return std::atof(_contents);
    }
    String s;
    s.setSize(_length);
    for (size_t i = 0; i < _length; i++) {
        if (checkAllowedFloatChars(_contents[i])) {
            s._contents[i] = _contents[i];
            continue;
        } else {
            break;
        }
    }
    return std::atof(s._contents);
}

bool String::checkAllowedFloatChars(const char s) const {
    for (size_t i = 0; i < 12; i++) {
        if (s == allowedFloatChars[i]) {
            return true;
        }
    }
    return false;
}

String String::getPart(const unsigned start, const unsigned end) const {
    String s;
    s.setSize(end - start + 1);
    unsigned j = 0;
    for (size_t i = start; i <= end; i++) {
        s._contents[j] = _contents[i];
        j++;
    }
    return s;
}

void String::split(const char d, StringArray* strArray) const {
    unsigned n = 0;
    unsigned start = 0;

    for (size_t i = 0; i < _length; i++) {
        if (_contents[i] == d) n++;
    }
    strArray->setSize(n+1);

    unsigned position = 0;

    for (size_t i = 0; i < _length; i++) {
        if (_contents[i] == d) {
            if (i != 0) {
                strArray->set(position, getPart(start, i-1));
            }
            position++;
            start = i+1;
        } else if (i == _length-1) {
            strArray->set(position, getPart(start, i));
        }
    }
}
