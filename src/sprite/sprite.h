//
//  sprite.h
//  Proto2
//
//  Created by Shaun West on 8/28/17.
//
//

#ifndef sprite_h
#define sprite_h

#include <iostream>

#include "util/geom.h"

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

struct SpriteAnimation {
  int frameset_id;
  std::string current_sequence;
  float duration_count;
  int current_sequence_index;
  bool flip;
};

enum SpriteDirection { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };
enum SpriteAi { AI_NONE, AI_BASIC };

// TODO change sprite type to int?
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

#endif
