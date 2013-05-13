//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#include "parser_impl.hpp"

#include "lexer.hpp"

namespace pickle_ {

parser_impl::parser_impl() {}

void parser_impl::load(std::istream &in) {
}

void parser_impl::load(const std::string &in) {
  lexer::get()->parse(in);
}

std::unique_ptr<pickle::value> parser_impl::query(const std::string& q) {
  return nullptr;
}

}  // namespace pickle_

std::unique_ptr<pickle::parser> pickle::new_parser() {
  return std::unique_ptr<pickle::parser>(new pickle_::parser_impl());
}
