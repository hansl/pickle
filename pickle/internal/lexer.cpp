//
//  lexer.cpp
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#include "lexer.hpp"

#include "y.tab.h"

int yyparse();

namespace pickle_ {

lexical_stack::lexical_stack() {}

lexer* lexer::get() {
  static lexer the_lexer;
  return &the_lexer;
}

std::unique_ptr<program> lexer::parse(const std::string& s) {
  if (program_ != nullptr) {
    throw new std::runtime_error("Parsing twice in the same program.");
  }
  program_ = std::unique_ptr<program>(new program());
  content_ = s;
  yyparse();
  return std::unique_ptr<program>(program_.release());
}

}

int lex_read(char *buffer, size_t *num, size_t max) {
  std::string& content = pickle_::lexer::get()->content_;

  std::string::iterator it;
  for (it = content.begin(); it != content.end() && --max > 0; ++it) {
    *(buffer++) = *it;
  }
  *num = it - content.begin();
  content.erase(content.begin(), it);
  return 0;
}
