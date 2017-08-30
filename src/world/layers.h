//
//  layers.h
//  Proto2
//
//  Created by Shaun West on 8/28/17.
//
//
// TODO rename layer.h

#ifndef layers_h
#define layers_h

#include <iostream>

#include "sprite/sprite.h"

#include "collision.h"

struct SpriteLayer {
  SpriteList sprites;
};

struct BackgroundLayer {
  std::string image_name;
};

struct CollisionLayer {
  CollisionBoxList boxes;
};

struct Layers {
  CollisionLayer collision_layer;
  SpriteLayer sprite_layer;
  BackgroundLayer background_layer;
};

#endif
