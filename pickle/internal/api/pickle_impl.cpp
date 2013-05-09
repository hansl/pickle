//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#include "pickle_impl.hpp"

namespace pickle {

pickle_impl::pickle_impl() {}

void pickle_impl::load(std::istream &in) {

}

void pickle_impl::load(const std::string &in) {

}

std::unique_ptr<value> pickle_impl::query(const std::string& q) {
  return nullptr;
}

std::unique_ptr<pickle> new_pickle() {
  return std::unique_ptr<pickle>(new pickle_impl());
}

}  // namespace pickle
