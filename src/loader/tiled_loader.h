//
//  tiled_loader.h
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#ifndef tiled_loader_h
#define tiled_loader_h

#include <iostream>

//#include "game/level_data.h"
#include "ninjagaiden/spec.h"
#include "json/json.h"

class TiledLoader
{
public:
  TiledLoader();
  Layers load(std::string json_path);
private:
  Layers get_layers(Json::Value layers_config);
  CollisionLayer get_collision_layer(Json::Value layer_config);
  CollisionBox get_collision_box(Json::Value box_config);
  SpriteLayer get_sprite_layer(Json::Value layer_config);
  Sprite get_sprite(Json::Value sprite_config);
  BackgroundLayer get_background_layer(Json::Value layer_config);
};

#endif /* tiled_loader_h */
