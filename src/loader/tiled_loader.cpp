//
//  tiled_loader.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "tiled_loader.h"

#include "util/util.h"
#include "util/log.h"

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
      continue;
    }

    if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == COLLISION_LAYER) {
      new_layers.collision_layer = get_collision_layer(layer_config);
    }
    else if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == SPRITE_LAYER) {
      new_layers.sprite_layer = get_sprite_layer(layer_config);
    }
    else if (layer_config[PROPERTIES_KEY][SUBTYPE_KEY] == BACKGROUND_LAYER) {
      new_layers.background_layer = get_background_layer(layer_config);
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
  IntRect rect(
    box_config["x"].asInt(),
    box_config["y"].asInt(),
    box_config["width"].asInt(),
    box_config["height"].asInt()
  );

  CollisionBox box = {rect, normal};

  return box;
}

// Get data for a single sprite layer from the provided JSON config
SpriteLayer TiledLoader::get_sprite_layer(Json::Value layer_config) {
  Json::Value objects = layer_config["objects"];
  SpriteLayer new_layer;

  for (int i = 0; i < objects.size(); ++i) {
    Json::Value object_config = objects[i];
    new_layer.sprites.push_back(get_sprite(object_config));
  }

  return new_layer;
}

Sprite TiledLoader::get_sprite(Json::Value sprite_config) {
  std::string sprite_id = sprite_config["id"].asString(); // TODO NOTE need to use id instead of name in config

  SpriteAnimation sprite_animation = {
    sprite_id, // Is this right?
    "idle"
  };

  // Create the sprite
  // Note: Tiled sets "y" value strangely. Need to subtract the height of the sprite
  // to get correct value
  Sprite sprite = {
    sprite_id,
    sprite_animation,
    IntVector2(
      sprite_config["x"].asInt(),
      sprite_config["y"].asInt() - sprite_config["height"].asInt()
    )
  };

  sprite.width = sprite_config["width"].asInt();
  sprite.height = sprite_config["height"].asInt();

  //sprite.frameset_id = sprite_config["name"].asString();

  return sprite;
}

BackgroundLayer TiledLoader::get_background_layer(Json::Value layer_config) {
  BackgroundLayer new_layer;
  new_layer.image_name = layer_config["image"].asString();
  return new_layer;
}
