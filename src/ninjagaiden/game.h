//
//  game.h
//  Proto2
//
//  Created by Shaun West on 6/11/17.
//
//

// PROJECT: error handling (for major errors at least)
// PROJECT: Render the Ninja Gaiden start screen and handle input
// PROJECT: Screen sizing/scaling
// PROJECT: Transition
// PROJECT: Better logging class

// best practices: how to handle errors

#ifndef game_h
#define game_h


// TODO make these constexpr instead?
#define WINDOW_TITLE    "Ninja Gaiden"
#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   480
#define FULLSCREEN      false
#define LOGICAL_WIDTH   256
#define LOGICAL_HEIGHT  240

#define ASSETS_IMAGES "assets/images"
#define ASSETS_FONTS  "assets/fonts"

#include "video/video_sdl.h"
#include "util/timer.h"
#include "util/util.h"
#include "control/nes_input_manager.h"

// TODO what are new C++11 best practices for enums?
enum ScreenId {
  TITLE_SCREEN,
  LEVEL_SCREEN
};

enum LevelId {
  LEVEL_NONE,
  LEVEL_1
};

enum Phase {
  CREATE,
  UPDATE
};

struct GameSpec {
  const AssetPaths asset_paths = {
    ASSETS_IMAGES, ASSETS_FONTS
  };
  WindowSpec window = {
    WINDOW_TITLE,
    {WINDOW_WIDTH, WINDOW_HEIGHT},
    {LOGICAL_WIDTH, LOGICAL_HEIGHT},
    FULLSCREEN
  };
  NESInput input;
  ScreenId current_screen = TITLE_SCREEN;
  LevelId current_level = LEVEL_NONE;
  Phase phase = CREATE;
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
