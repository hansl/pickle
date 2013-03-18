//
//  lexer.h
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#ifndef __pickle__lexer__
#define __pickle__lexer__

#include <string>
#include <vector>

class lexical_stack {
public:
  class entry {
  public:
    void new_line() { ln_++; }
    int get_ln() { return ln_; }
  private:
    entry(std::string filename) : filename_(filename), ln_(1) {}
    std::string filename_;
    int ln_;
  };

  static lexical_stack* get();

public:
  entry& top() { return stack_.back(); }
  void pop() { return stack_.pop_back(); }

  void new_line() { top().new_line(); }

private:
  lexical_stack();
  std::vector<entry> stack_;
};

#endif /* defined(__pickle__lexer__) */
