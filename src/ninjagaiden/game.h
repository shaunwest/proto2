//
//  game.h
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

// PROJECT 1: Render the Ninja Gaiden start screen and handle input
// PROJECT 2: Screen sizing/scaling
// PROJECT 3: Render debug info
// PROJECT 4: Transition

// best practices: how to handle errors

#ifndef game_h
#define game_h

#define WINDOW_TITLE  "Ninja Gaiden"
#define WINDOW_WIDTH  512
#define WINDOW_HEIGHT 480
#define RES_WIDTH     256
#define RES_HEIGHT    240

#define ASSETS_IMAGES "assets/images"
#define ASSETS_FONTS  "assets/fonts"

#include "video/renderer_sdl.h"
#include "util/timer.h"
#include "util/util.h"
#include "control/nes_input_manager.h"

enum ScreenId {
  TITLE_SCREEN,
  LEVEL_SCREEN
};

enum LevelId {
  LEVEL_NONE,
  LEVEL_1
};

struct GameSpec {
  AssetPaths asset_paths = {
    ASSETS_IMAGES, ASSETS_FONTS
  };
  WindowSpec window = {
    WINDOW_TITLE,
    {WINDOW_WIDTH, WINDOW_HEIGHT},
    {RES_WIDTH, RES_HEIGHT}
  };
  NESInput input;
  ScreenId current_screen = TITLE_SCREEN;
  LevelId current_level = LEVEL_NONE;
};

class Game {
public:
  Game();
  Game(GameSpec game_spec);
  int start();
private:
  GameTimer timer;
  GameSpec game_spec;
};

#endif /* game_h */
