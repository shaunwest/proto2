//
//  game.h
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

// PROJECT: error handling (for major errors at least). Disable exceptions?
// PROJECT: Do transition from title to game screen


#ifndef game_h
#define game_h

#include "util/timer.h"
#include "spec.h"

class Game {
public:
  Game();
  Game(GameSpec game_spec);
  int start();
private:
  GameTimer timer;
  GameSpec game_spec;
};

#endif
