//
//  lexer.cpp
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#include "lexer.hpp"

pickle_::lexical_stack::lexical_stack() {}

pickle_::lexical_stack* pickle_::lexical_stack::get() {
  static lexical_stack the_stack;
  return &the_stack;
}

pickle_::program pickle_::lexer::parse(const std::string& str) {
  
}
