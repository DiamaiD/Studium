// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#ifndef ENTITY_H_
#define ENTITY_H_

#include <gtest/gtest.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Entity {
 public:
  Entity();
  explicit Entity(const string& name);
  virtual ~Entity();
  string getName() const;
  virtual void addTriple(const vector<string>& triple);
  virtual string toString() const;

 protected:
  string _name;

  FRIEND_TEST(EntityTest, blackbox);
  FRIEND_TEST(PersonTest, blackbox);
  FRIEND_TEST(FilmTest, blackbox);
};

class Person : public Entity {
 public:
  explicit Person(const string& name);
  ~Person();
  void addTriple(const vector<string>& triple);
  string toString() const;
 private:
  string _placeOfBirth;

  FRIEND_TEST(PersonTest, blackbox);
};

class Film : public Entity {
 public:
  explicit Film(const string& name);
  ~Film();
  void addTriple(const vector<string>& triple);
  string toString() const;

 private:
  vector<string> _crew;
  FRIEND_TEST(FilmTest, blackbox);
};

#endif  // ENTITY_H_
