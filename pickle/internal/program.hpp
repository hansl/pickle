//
//  program.hpp
//
//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#ifndef PICKLE_API_PROGRAM_HH__
#define PICKLE_API_PROGRAM_HH__

#include "statement.hpp"

#include <memory>
#include <vector>

namespace pickle_ {

  class program {
  public:
    typedef std::vector<std::shared_ptr<statement>>::const_iterator
        program_iterator;

  public:
    program() {}

    void add_statement(std::shared_ptr<statement>& s) {
      statements_.push_back(s);
    }

    const program_iterator begin() const { return statements_.begin(); }
    const program_iterator end() const { return statements_.end(); }

  private:
    std::vector<std::shared_ptr<statement>> statements_;
  };

} // end namespace pickle_

#endif // PICKLE_API_PROGRAM_HH__
