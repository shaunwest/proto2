//
//  spec.h
//  Proto2
//
//  Created by Shaun West on 8/7/17.
//
//

#ifndef spec_h
#define spec_h

#include <iostream>
#include <vector>
#include <map>

#include "ninjagaiden/game_config.h"
#include "util/geom.h"
#include "video/video_sdl.h"
#include "control/nes_input_manager.h"
#include "loader/aseprite_loader.h"

// TODO what are new C++11 best practices for enums?

// TODO get rid of all these defaults
struct PhysicsAttributes {
  float move_max_speed = 3;
  float fall_max_speed = 6;
  float jump_max_speed = 15;
};

struct Physics {
  Vector2f velocity;
  Vector2f acceleration;
  PhysicsAttributes attrs;
};

// TODO Rename to something that doesn't have 'Physics' in it?
struct PhysicsFlags {
  bool jump_cancel;
  bool colliding_with_floor;
  bool colliding_with_left_wall;
  bool colliding_with_right_wall;
  bool colliding_with_ceiling;
};

enum CollisionType {
  COLLISION_TYPE_NORMAL, COLLISION_TYPE_PASSTHRU
};

struct CollisionBox {
  Recti rect;
  CollisionType type;
};

typedef std::vector<CollisionBox> CollisionBoxList;

struct CollisionLayer {
  CollisionBoxList boxes;
};

struct SpriteAnimation {
  int frameset_id;
  std::string current_sequence;
  float duration_count;
  int current_sequence_index;
  bool flip;
};

enum SpriteDirection { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };
enum SpriteAi { AI_NONE, AI_BASIC };

struct Sprite {
  int frameset_id;
  std::string type;
  SpriteAnimation animation;
  Vector2i position;
  Size size;
  SpriteDirection dir;
  Recti bounds;
  Physics physics;
  PhysicsFlags flags;
};

typedef std::vector<Sprite> SpriteList;

struct SpriteLayer {
  SpriteList sprites;
};

struct BackgroundLayer {
  std::string image_name;
};

struct Layers {
  CollisionLayer collision_layer;
  SpriteLayer sprite_layer;
  BackgroundLayer background_layer;
};

/*
struct CameraSpec {
  Vector2i position;
  Size viewport;
};

struct Level {
  SpriteFrameset player_frameset;
  SpriteFramesets sprite_framesets;
  Layers layers;
  Sprite player;
  CameraSpec camera;
};
*/

/*
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
*/

struct Game {
  WindowSpec window = {
    WINDOW_TITLE,
    { WINDOW_WIDTH, WINDOW_HEIGHT },
    { LOGICAL_WIDTH, LOGICAL_HEIGHT },
    WINDOW_SCALE,
    FULLSCREEN
  };
  NESInput input;
  ViewMode view_mode;
  PlayerStats player_stats = {
    START_LIVES, START_SCORE, START_NINPO, START_ITEM
  };
  /*
  Level level = {
    {}, // Player frameset // TODO Ehhh... annoying that I don't know what these represent without comments
    {}, // Sprite framesets
    {}, // Layers
    {   // Player
      0, // Sprite frameset id
      "player",
      { // Animation
        FRAMESET_DEFAULT_ID,
        PLAYER_START_ANIMATION,
        ANIMATION_DEFAULT_DURATION,
        ANIMATION_START_INDEX,
        false // flip
      },
      { PLAYER_START_X, PLAYER_START_Y },
      { PLAYER_WIDTH, PLAYER_HEIGHT },
      DIR_RIGHT,
      { 10, 0, 12, 32 } // bounds
    },
    { // Camera
      { CAMERA_START_X, CAMERA_START_Y },
      { CAMERA_VIEW_WIDTH, CAMERA_VIEW_HEIGHT }
    }
  };
  */
};

#endif
