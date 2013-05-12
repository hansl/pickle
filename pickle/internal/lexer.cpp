//
//  lexer.cpp
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#include "lexer.hpp"

namespace pickle_ {

lexical_stack::lexical_stack() {}

lexical_stack* lexical_stack::get() {
  static lexical_stack the_stack;
  return &the_stack;
}

std::unique_ptr<program> lexer::parse(const std::string& s) {
  std::unique_ptr<program> p(new program());
  return std::unique_ptr<program>(p.release());
}

}

int lex_nextchar( char *buffer, int *numBytesRead, int maxBytesToRead ) {
  return 0;
}
