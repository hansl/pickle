#ifndef PICKLE__VALUE_H__
#define PICKLE__VALUE_H__

#include <string>
#include "expression.hh"

namespace pickle {

enum value_type {
  TYPE_UNDEFINED = 0,
  TYPE_NULL,
  TYPE_BOOLEAN,
  TYPE_INTEGER,
  TYPE_DOUBLE,
  TYPE_STRING,
  TYPE_LIST,
  TYPE_MAP,

  TYPE_EXPRESSION = -1  // Not const and not evaluated.
};

class value_internal : public value, expression {
 public:
  // Type validation.
  bool is_undefined() const;
  bool is_null() const;
  bool is_boolean() const;
  bool is_integer() const;
  bool is_double() const;
  bool is_string() const;
  bool is_list() const;
  bool is_map() const;

  // Conversion methods. Converting an undefined value causes an exception
  // and converting a null returns the default value for the type.
  // Non-primitive types are non-convertible.
  bool as_boolean() const;
  int64_t as_integer() const;
  double as_double() const;
  std::string as_string() const;

  // If the type is not a list, this will return an undefined value.
  value& value_at_index(int index) const;
  // If the type is not a map, this will return an undefined value.
  value& value_with_key(const string& key) const;

  // Returns a debug string representation of the value.
  string debug_string() const;

 protected:
  friend class expression;

  static value undefined_value_;

  value_type_e type_;
};

} // pickle

#endif // PICKLE__VALUE_H__