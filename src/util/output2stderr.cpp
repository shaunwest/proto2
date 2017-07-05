//
//  output2stderr.cpp
//  Proto2
//
//  Created by Shaun West on 6/21/17.
//
//

#include "output2stderr.h"

#include <sstream>

void Output2Stderr::output(const std::string &msg) {
  fprintf(stderr, "%s", msg.c_str());
  fflush(stderr);
}
