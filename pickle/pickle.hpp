#ifndef PICKLE_HH__
#define PICKLE_HH__

#include <string>

// C++ Header for the pickle API.

namespace pickle {

class value {
 public:
  virtual bool as_boolean() const = 0;
  virtual int64_t as_integer() const = 0;
  virtual double as_double() const = 0;
  virtual std::string as_string() const = 0;

  
 protected:
  value() {};
};

#endif // PICKLE_HH__