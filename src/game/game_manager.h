//
//  game_manager.h
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

// PROJECT: error handling (for major errors at least). Disable exceptions?
// PROJECT: Do transition from title to game screen


#ifndef game_manager_h
#define game_manager_h

#include "game.h"
#include "util/timer.h"
#include "control/nes_input_manager.h"

class GameManager {
public:
  GameManager(); // TODO is this needed?
  GameManager(Game game);
  int start();
private:
  GameTimer timer;
  Game game;
  NESInput input;
};

#endif
