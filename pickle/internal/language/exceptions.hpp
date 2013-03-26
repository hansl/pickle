//
//  exceptions.h
//  pickle
//
//  Created by Hans Larsen on 3/25/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#ifndef __pickle__exceptions__
#define __pickle__exceptions__

#include <iostream>

class LexicalError : public std::runtime_error {
public:
  LexicalError(std::string msg) : std::runtime_error(msg) {}
};

class SyntaxError : public std::runtime_error {
public:
  SyntaxError(std::string msg) : std::runtime_error(msg) {}
};

#endif /* defined(__pickle__exceptions__) */
