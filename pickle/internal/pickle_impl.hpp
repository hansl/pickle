//
//  pickle.hpp
//
//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#ifndef PICKLE_API_PICKLE_HH__
#define PICKLE_API_PICKLE_HH__

#include "pickle.hpp"
#include <exception>
#include <iostream>
#include <string>

// C++ Header for the pickle API.

namespace pickle_ {

class pickle_impl : public pickle {
public:
  pickle_impl();

  void load(std::istream& in);
  void load(const std::string& in);
  std::unique_ptr<value> query(const std::string& query);

private:
  
};

} // end namespace pickle+

#endif // PICKLE_API_PICKLE_HH__
