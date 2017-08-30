//
//  game.h
//  Proto2
//
//  Created by Shaun West on 8/7/17.
//

#ifndef game_h
#define game_h

#define WINDOW_TITLE    "Ninja Gaiden Demo"
#define WINDOW_WIDTH    256 // 294 // <- more accurate
#define WINDOW_HEIGHT   240
#define WINDOW_SCALE    2
#define FULLSCREEN      false
#define LOGICAL_WIDTH   256
#define LOGICAL_HEIGHT  240

#define START_LIVES 3
#define START_SCORE 0
#define START_NINPO 0
#define START_ITEM  ITEM_NONE

#include <iostream>
#include "util/geom.h"
#include "video/video_sdl.h"

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
  MODE_LOAD_TITLE,
  MODE_LOAD_LEVEL_1,
  MODE_UPDATE
};

struct Game {
  WindowSpec window = {
    WINDOW_TITLE,
    { WINDOW_WIDTH, WINDOW_HEIGHT },
    { LOGICAL_WIDTH, LOGICAL_HEIGHT },
    WINDOW_SCALE,
    FULLSCREEN
  };
  std::string levelPath;
  ViewMode view_mode;
  PlayerStats player_stats = {
    START_LIVES, START_SCORE, START_NINPO, START_ITEM
  };
};

#endif
