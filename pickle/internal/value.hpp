#ifndef PICKLE__VALUE_H__
#define PICKLE__VALUE_H__

#include "expression.hpp"

#include <memory>
#include <sstream>
#include <string>

namespace pickle_ {

enum value_type_e {
  type_null = 0,
  type_boolean,
  type_integer,
  type_double,
  type_string,
  type_list,
  type_map,

  type_expression = -1  // Not const and not evaluated.
};

class value_internal : public pickle::value, expression {
 public:
  // Type validation.
  bool is_null() const { return type_ == type_null; }
  bool is_boolean() const { return type_ == type_boolean; }
  bool is_integer() const { return type_ == type_integer; }
  bool is_double() const { return type_ == type_double; }
  bool is_string() const { return type_ == type_string; }
  bool is_list() const { return type_ == type_list; }
  bool is_map() const { return type_ == type_map; }

  // Conversion methods. Converting a null throws an exception.
  // Non-primitive types are non-convertible.
  bool as_boolean() const = 0;
  int64_t as_integer() const = 0;
  double as_double() const = 0;
  std::string as_string() const = 0;

  // If the type is not a list, this will return an undefined value.
  std::unique_ptr<value> value_at_index(int index) const = 0;
  // If the type is not a map, this will return an undefined value.
  std::unique_ptr<value> value_with_key(const std::string& key) const = 0;

  // Returns a debug string representation of the value.
  std::string debug_string() const;

 protected:
  value_internal(value_type_e type) : type_(type) {}

  friend class expression;

  value_type_e type_;
};

class integer_value : public value_internal {
 public:
  integer_value(long l) : value_(l), value_internal(type_integer) {}

  // Type validation.
  bool is_null() const { return type_ == type_null; }
  bool is_boolean() const { return type_ == type_boolean; }
  bool is_integer() const { return type_ == type_integer; }
  bool is_double() const { return type_ == type_double; }
  bool is_string() const { return type_ == type_string; }
  bool is_list() const { return type_ == type_list; }
  bool is_map() const { return type_ == type_map; }

  // Conversion methods. Converting a null throws an exception.
  // Non-primitive types are non-convertible.
  bool as_boolean() const { return value_ != 0; }
  int64_t as_integer() const { return value_; }
  double as_double() const { return value_; }
  std::string as_string() const {
    std::ostringstream oss;
    oss << value_;
    return oss.str();
  }

  // If the type is not a list, this will return an undefined value.
  std::unique_ptr<value> value_at_index(int index) const {
    throw new pickle::conversion_error("integer", "list");
  }
  // If the type is not a map, this will return an undefined value.
  std::unique_ptr<value> value_with_key(const std::string& key) const {
    throw new pickle::conversion_error("integer", "map");
  }

 private:
  int64_t value_;
};

} // pickle

#endif // PICKLE__VALUE_H__