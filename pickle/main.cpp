//
//  main.cpp
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#include <fstream>
#include <iostream>

#include "pickle.hpp"

int main(int argc, const char * argv[])
{
  std::string x = "param = 1;";
  pickle::parser* p = pickle::new_parser().release();
  p->load(x);
  std::cout << p->query("param").get();
  return 0;
}

