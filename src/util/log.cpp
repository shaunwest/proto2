//
//  log.cpp
//  Proto2
//
//  Created by Shaun West on 7/24/17.

#include "log.h"

Logger::Logger() {};

std::ostringstream & Logger::out(LogLevel level) {
  os << time_now();
  os << " " << log_level2str(level) << ": ";

  return os;
}

void Logger::output(const std::string &msg) {
  fprintf(stderr, "%s", msg.c_str());
  fflush(stderr);
}

Logger::~Logger() {
  os << std::endl;
  output(os.str());
}
