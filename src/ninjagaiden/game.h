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

// TODO move these to app-config?
#define WINDOW_TITLE    "Ninja Gaiden"
#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   480
#define FULLSCREEN      false
#define LOGICAL_WIDTH   256
#define LOGICAL_HEIGHT  240

#define START_LIVES 3
#define START_SCORE 0
#define START_NINPO 0
#define START_ITEM  ITEM_NONE

#define PLAYER_START_ANIMATION      "idle"
#define PLAYER_START_X              0
#define PLAYER_START_Y              0
#define PLAYER_WIDTH                32
#define PLAYER_HEIGHT               32
#define FRAMESET_DEFAULT_ID         0
#define ANIMATION_DEFAULT_DURATION  0
#define ANIMATION_START_INDEX       0

#include "video/video_sdl.h"
#include "util/timer.h"
#include "util/util.h"
#include "control/nes_input_manager.h"
#include "game/level_data.h"
#include "game/screen_view.h"

// TODO what are new C++11 best practices for enums?

/*
enum LevelId {
  LEVEL_NONE,
  LEVEL_1
};
*/

enum ItemId {
  ITEM_NONE,
  ITEM_SHURIKEN,
  ITEM_SPIN
};

struct PlayerStats {
  char lives;
  unsigned int score;
  char ninpo;
  ItemId item;
};

enum ViewMode {
  VIEW_SCREEN, VIEW_LEVEL
};

struct GameSpec {
  WindowSpec window = {
    WINDOW_TITLE,
    {WINDOW_WIDTH, WINDOW_HEIGHT},
    {LOGICAL_WIDTH, LOGICAL_HEIGHT},
    FULLSCREEN
  };
  NESInput input;
  //LevelId current_level_id = LEVEL_NONE; // TODO move to level spec
  ViewMode view_mode;
  ScreenId screen_id;
  PlayerStats player_stats = {
    START_LIVES, START_SCORE, START_NINPO, START_ITEM
  };
  LevelSpec level_spec = {
    LEVEL_1,
    {},
    {},
    {
      "player", // sprite type
      {
        FRAMESET_DEFAULT_ID,
        PLAYER_START_ANIMATION,
        ANIMATION_DEFAULT_DURATION,
        ANIMATION_START_INDEX
      },
      { PLAYER_START_X, PLAYER_START_Y },
      PLAYER_WIDTH,
      PLAYER_HEIGHT,
      DIR_RIGHT
    }
  };
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
