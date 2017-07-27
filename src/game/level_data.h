//
//  level_data.h
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
// TODO some of this stuff may be too game specific to go here
//

#ifndef level_data_h
#define level_data_h

#include "util/util.h"

#include <iostream>
#include <vector>
#include <map>

struct PhysicsAttributes {
  float move_max_speed = 3;
  float fall_max_speed = 6;
  float jump_max_speed = 15;
};

struct PhysicsState {
  FloatVector2 velocity;
  FloatVector2 acceleration = FloatVector2(0.0, 0.0);
  PhysicsAttributes attrs;
};

struct PhysicsFlags {
  bool jump_cancel = false;
  bool colliding_with_floor = false;
  bool colliding_with_left_wall = false;
  bool colliding_with_right_wall = false;
  bool colliding_with_ceiling = false;
};

enum CollisionType {
  normal, passthru
};

struct CollisionBox {
  IntRect rect;
  CollisionType type;
};

typedef std::vector<CollisionBox> CollisionBoxList;

struct CollisionLayer {
  CollisionBoxList boxes;
};

struct SpriteFrame {
  int atlas_x;
  int atlas_y;
  float duration;
  bool rotated;
};

typedef std::map<std::string, std::vector<SpriteFrame>> FrameMap;

struct SpriteFrameset {
  int sprite_width;
  int sprite_height;
  std::string current_sequence;
  FrameMap frames;
};

typedef std::map<std::string, SpriteFrameset> SpriteFramesetList;

/*
struct SpriteAnimation {
  std::string frameset_id = "default";
  std::string current_sequence = "default";
  float duration_count = 0.0f;
  int current_sequence_index = 0;
};
*/

struct SpriteAnimation {
  std::string frameset_id;
  std::string current_sequence;
  float duration_count;
  int current_sequence_index;
};

enum SpriteDirection { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN };
enum SpriteAi { AI_NONE, AI_BASIC };

struct Sprite {
  std::string sprite_id;
  SpriteAnimation animation;
  IntVector2 position;
  int width; // TODO use Size
  int height;
  SpriteDirection dir;
  IntRect hitbox;
  PhysicsState physics;
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

#endif /* level_data_h */
