
#include "app-config.h"

#include "json/json.h"
#include "util/log.h"
#include "ninjagaiden/game_manager.h"

#define STRINGIFY(x) x
#define STRINGIFYMACRO(y) STRINGIFY(y)

int main(int argc, char *argv[]) {
  LOG(LOG_INFO) << "NINJA GAIDEN DEMO VERSION: " << STRINGIFYMACRO(Proto2_VERSION_MAJOR) << "."
    << STRINGIFYMACRO(Proto2_VERSION_MINOR);

  return GameManager().start();
}
