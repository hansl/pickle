//
//  statement.hpp
//
//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//
#ifndef PICKLE_INTERNAL_STATEMENT_HH__
#define PICKLE_INTERNAL_STATEMENT_HH__

#include <memory>
#include <vector>

namespace pickle_ {
  namespace pcl {

  class statement {
  public:
    statement() {}

    virtual void execute(void* environment, void* scope) const = 0;
  };

  class assignment_statement : public statement {
  public:
    assignment_statement(const char* symbol, void* expr) {}

    void execute(void* environment, void* scope) const {};
  };

  } // end namespace pcl
} // end namespace pickle_

#endif // PICKLE_API_PROGRAM_HH__
