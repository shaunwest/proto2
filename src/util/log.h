//
//  log.h
//  Proto2
//
//  Created by Shaun West on 6/19/17.
//
//  This class is slightly based on the code described here:
//  http://www.drdobbs.com/cpp/logging-in-c/201804215
//

#ifndef log_h
#define log_h

#define LOG(level) \
if (level <= Logger::reportingLevel) \
Logger().out(level)

#include <sstream>

#include "util/util.h"

enum LogLevel {LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG};

inline std::string log_level2str(LogLevel level) {
  switch(level) {
    case LOG_ERROR:
      return "ERR";
    case LOG_WARNING:
      return "WRN";
    case LOG_INFO:
      return "INF";
    case LOG_DEBUG:
      return "DBG";
    default:
      return "???";
  }
}

class Logger
{
public:
  Logger();
  ~Logger();
  std::ostringstream & out(LogLevel level = LOG_INFO);
public:
  static LogLevel reportingLevel;
  static void output(const std::string &msg);
protected:
  std::ostringstream os;
};

#endif /* log_h */
