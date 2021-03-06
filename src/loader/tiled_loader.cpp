//
//  tiled_loader.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "tiled_loader.h"

#include "util/geom.h"
#include "util/log.h"
#include "util/util.h"

#define PROPERTIES_KEY "properties"
#define SUBTYPE_KEY "subtype"
#define COLLISION_LAYER "collision"
#define SPRITE_LAYER "sprite"
#define BACKGROUND_LAYER "background"

TiledLoader::TiledLoader() {}

Layers TiledLoader::load(std::string json_path) {
  Json::Value json_config = get_json("assets/" + json_path);
  return get_layers(json_config["layers"]);
};

// Get all layers data from the provided JSON config
Layers TiledLoader::get_layers(Json::Value layers_config) {
  Layers new_layers;

  for (auto layer_config : layers_config) {
    if (!layer_config.isMember(PROPERTIES_KEY)) {
      LOG(LOG_ERROR) << "TiledLoader: No properties key!";
      continue;
    }

    if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == COLLISION_LAYER) {
      new_layers.collision = get_collision_layer(layer_config);
    }
    else if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == SPRITE_LAYER) {
      new_layers.sprite = get_sprite_layer(layer_config);
    }
    else if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == BACKGROUND_LAYER) {
      new_layers.background = get_background_layer(layer_config);
    }
    else {
      LOG(LOG_WARNING) << "No valid subtype found for layer.";
    }
  }

  return new_layers;
}

// Get data for a single collision layer from the provided JSON config
CollisionLayer TiledLoader::get_collision_layer(Json::Value layer_config) {
  Json::Value objects = layer_config["objects"];
  CollisionLayer new_layer;

  for (int i = 0; i < objects.size(); ++i) {
    Json::Value object = objects[i];

    if (object.isMember("polyline")) {
      LOG(LOG_WARNING) << "Polyline isn't implemented!";
    }
    else {
      new_layer.boxes.push_back(get_collision_box(object));
    }
  }

  return new_layer;
}

// Get a Rect representing a collision box from the provided JSON config
CollisionBox TiledLoader::get_collision_box(Json::Value box_config) {
  Recti rect(
    box_config["x"].asInt(),
    box_config["y"].asInt(),
    box_config["width"].asInt(),
    box_config["height"].asInt()
  );

  CollisionBox box = {rect, COLLISION_TYPE_NORMAL};

  return box;
}

// Get data for a single sprite layer from the provided JSON config
SpriteLayer TiledLoader::get_sprite_layer(Json::Value layer_config) {
  Json::Value objects = layer_config["objects"];
  SpriteLayer new_layer;

  // TODO for range
  //for (int i = 0; i < objects.size(); ++i) {
  for (auto object_config : objects) {
    //Json::Value object_config = objects[i];
    new_layer.sprites.push_back(get_sprite(object_config));
  }

  return new_layer;
}

Sprite TiledLoader::get_sprite(Json::Value sprite_config) {
  // TODO how do you link a sprite animation to a frameset?
  SpriteAnimation sprite_animation = {
    0, // frameset unknown currently
    "idle"
  };

  int type = (sprite_config.isMember(PROPERTIES_KEY) &&
      sprite_config[PROPERTIES_KEY].isMember("frameset")) ?
    sprite_config[PROPERTIES_KEY]["frameset"].asInt() : 0;

  // Create the sprite
  Sprite sprite = {
    type,
    sprite_config["type"].asString(),
    sprite_animation,
    {
      sprite_config["x"].asInt(),
      sprite_config["y"].asInt()
    }
  };

  sprite.size.width = sprite_config["width"].asInt();
  sprite.size.height = sprite_config["height"].asInt();

  //sprite.frameset_id = sprite_config["name"].asString();

  return sprite;
}

BackgroundLayer TiledLoader::get_background_layer(Json::Value layer_config) {
  BackgroundLayer layer;
  layer.image_name = layer_config["image"].asString();
  layer.position = {
    layer_config["offsetx"].asInt(),
    layer_config["offsety"].asInt()
  };

  return layer;
}
