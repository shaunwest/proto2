
#include "app-config.h"

#include "util/log.h"
#include "ninjagaiden/game.h"

#include <iostream>

#define STRINGIFY(x) x
#define STRINGIFYMACRO(y) STRINGIFY(y)

template<> LogLevel Log<Output2Stderr>::reportingLevel = LOG_DEBUG;

int main(int argc, char *argv[]) {
  std::cout << "PROTO2 VERSION: " << STRINGIFYMACRO(Proto2_VERSION_MAJOR) << "." << STRINGIFYMACRO(Proto2_VERSION_MINOR) << std::endl;
  
  return Game().start();
}
