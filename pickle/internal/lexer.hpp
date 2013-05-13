//
//  lexer.h
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#ifndef __pickle__lexer__
#define __pickle__lexer__

#include "program.hpp"

#include <memory>
#include <string>
#include <vector>

int lex_read(char *buffer, size_t *num, size_t max);

namespace pickle_ {

class lexical_stack {
protected:
  class entry {
  public:
    void new_line() { ln_++; }
    int get_ln() { return ln_; }
  private:
    entry(std::string filename) : filename_(filename), ln_(1) {}
    std::string filename_;
    int ln_;

    friend class lexical_stack;
  };

public:
  entry& top() { return stack_.back(); }
  void pop() { return stack_.pop_back(); }
  void push(std::string filename) { stack_.push_back(entry(filename)); }

  void new_line() { top().new_line(); }

private:
  lexical_stack();
  std::vector<entry> stack_;

  friend class lexer;
};

class lexer {
public:
  static lexer* get();

  std::unique_ptr<program> parse(const std::string& s);

  program& current_program() {
    return *program_.get();
  }

  lexical_stack& stack() {
    return stack_;
  }

private:
  std::unique_ptr<program> program_;
  lexical_stack stack_;
  std::string content_;

  friend int ::lex_read(char *buffer, size_t *num, size_t max);
};

}  // namespace pickle_

#endif /* defined(__pickle__lexer__) */
