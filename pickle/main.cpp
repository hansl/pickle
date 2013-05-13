//
//  main.cpp
//  pickle
//
//  Created by Hans Larsen on 3/17/13.
//  Copyright (c) 2013 Hans Larsen. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <memory>

#include "pickle.hpp"

int main(int argc, const char * argv[])
{
  try {
    std::string x = "param = 1;";
    std::shared_ptr<pickle::parser> p(pickle::new_parser());
    p->load(x);
    std::cout << p->query("param").get();
  }
  catch( std::exception* e ) {
    std::cout << "Exception: " << e->what() << std::endl;
  }
  return 0;
}

