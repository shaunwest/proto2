//
//  log.h
//  Proto2
//
//  Created by Shaun West on 6/19/17.
//
//  This class is based on the code described here:
//  http://www.drdobbs.com/cpp/logging-in-c/201804215
//
//  C++ Notes:
//  The implementation of a template class or function must be in the same file as its declaration.
//  http://www.cplusplus.com/doc/oldtutorial/templates/
//
//  TODO does it make more sense to use runtime polymorphism instead of templates? I want to
//  pass a param to the app to make it log to file rather than console (or not log at all)
//  TODO need output 2 file policy

#ifndef log_h
#define log_h

#include <sstream>

#include "output2stderr.h"
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

template <typename OutputPolicy>
class Log
{
public:
  Log();
  ~Log();
  std::ostringstream & out(LogLevel level = LOG_INFO);
public:
  static LogLevel reportingLevel;
protected:
  std::ostringstream os;
};

typedef Log<Output2Stderr> LogStderr;

template <typename OutputPolicy>
Log<OutputPolicy>::Log() {};

template <typename OutputPolicy>
std::ostringstream & Log<OutputPolicy>::out(LogLevel level) {
  os << time_now();
  os << " " << log_level2str(level) << ": ";
  
  return os;
}

template <typename OutputPolicy>
Log <OutputPolicy>::~Log()
{
  os << std::endl;
  OutputPolicy::output(os.str());
}

#define LOG(level) \
if (level <= LogStderr::reportingLevel) \
LogStderr().out(level)

#endif /* log_h */
