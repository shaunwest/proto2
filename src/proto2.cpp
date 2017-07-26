
#include "app-config.h"

#include "json/json.h"
#include "util/log.h"
#include "ninjagaiden/game.h"

#include <iostream>

#define STRINGIFY(x) x
#define STRINGIFYMACRO(y) STRINGIFY(y)

int main(int argc, char *argv[]) {
  std::cout << "NINJA GAIDEN DEMO VERSION: " << STRINGIFYMACRO(Proto2_VERSION_MAJOR) << "."
    << STRINGIFYMACRO(Proto2_VERSION_MINOR) << std::endl;
  return Game().start();
}
