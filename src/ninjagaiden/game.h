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

#include "video/video_sdl.h"
#include "util/timer.h"
#include "util/util.h"
#include "control/nes_input_manager.h"

// TODO what are new C++11 best practices for enums?
enum ViewId {
  VIEW_TITLE,
  VIEW_LEVEL
};

enum LevelId {
  LEVEL_NONE,
  LEVEL_1
};

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

/*
// TODO Move to a sprite header?
enum SpriteDirection { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };

// TODO Move to a sprite header?
struct SpriteData {
  IntVector2 position;
  IntRect hitbox; // is it always the same in NG?
  SpriteDirection direction;
};
*/

struct GameSpec {
  WindowSpec window = {
    WINDOW_TITLE,
    {WINDOW_WIDTH, WINDOW_HEIGHT},
    {LOGICAL_WIDTH, LOGICAL_HEIGHT},
    FULLSCREEN
  };
  NESInput input;
  ViewId current_view_id = VIEW_TITLE;
  LevelId current_level_id = LEVEL_NONE;
  PlayerStats player_stats = {
    START_LIVES, START_SCORE, START_NINPO, START_ITEM
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
