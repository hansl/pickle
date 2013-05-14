//
//  pickle.hpp
//
//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#ifndef PICKLE_HH__
#define PICKLE_HH__

#include <exception>
#include <iostream>
#include <memory>
#include <string>

// C++ Header for the pickle API.

namespace pickle {

class lexical_error : public std::runtime_error {
public:
  lexical_error(std::string msg) : std::runtime_error(msg) {}
};

class syntax_error : public std::runtime_error {
public:
  syntax_error(std::string msg) : std::runtime_error(msg) {}
};

class conversion_error : public std::runtime_error {
 public:
  conversion_error(std::string from, std::string to) :
      std::runtime_error("Error converting from " + from + " to " + to) {}
};

class value {
 public:
  virtual bool as_boolean() const = 0;
  virtual int64_t as_integer() const = 0;
  virtual double as_double() const = 0;
  virtual std::string as_string() const = 0;

  virtual std::unique_ptr<value> value_at_index(int index) const = 0;
  virtual std::unique_ptr<value> value_with_key(const std::string& key) const
      = 0;

  virtual std::unique_ptr<value> operator[](int index) const {
    return value_at_index(index);
  }
  virtual std::unique_ptr<value> operator[](const std::string& index) const {
    return value_with_key(index);
  }

 protected:
  value() {};
};


class parser {
 public:
  virtual void load(std::istream& in) = 0;
  virtual void load(const std::string& in) = 0;
  virtual std::unique_ptr<value> query(const std::string& query) = 0;

 protected:
  parser() {};
};

std::unique_ptr<pickle::parser> new_parser();

} // end namespace pickle

#endif // PICKLE_HH__
