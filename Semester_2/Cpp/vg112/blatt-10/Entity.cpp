// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <string>
#include <vector>
#include "./Entity.h"

using std::string;
using std::vector;

Entity::Entity() {
  _name = "";
}

Entity::~Entity() { }

Entity::Entity(const string& name) {
  _name = name;
}

string Entity::getName() const {
  return _name;
}

void Entity::addTriple(const vector<string>& triple) { }

string Entity::toString() const {
  return _name;
}

Person::Person(const string& name) {
  _name = name;
  _placeOfBirth = "None";
}

Person::~Person() { }

void Person::addTriple(const vector<string>& triple) {
  if (triple[1] == "place of birth") {
    _placeOfBirth = triple[2];
  }
}

string Person::toString() const {
  if (_placeOfBirth != "None") {
    return _name + " place of birth: " + _placeOfBirth;
  } else {
    return _name;
  }
}

Film::Film(const string& name) {
  _name = name;
}

Film::~Film() { }

void Film::addTriple(const vector<string>& triple) {
  if (triple[1] == "cast member") {
    _crew.push_back(triple[2]);
  }
}

string Film::toString() const {
  if (_crew.size() == 0) return _name;

  string s = _name + " cast member: ";

  for (size_t i = 0; i < _crew.size(); i++) {
    if (i == 0) {
      s += _crew[i];
    } else {
      s += ", " + _crew[i];
    }
  }
  return s;
}
