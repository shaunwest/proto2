//
//  level.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level.h"

#include "game/level_data.h"
#include "loader/tiled_loader.h"

#define LEVELS_BASE_PATH "assets/levels/"

Level::Level(std::string level_path, VideoSDL &video) {
  TiledLoader level_loader;
  layers = level_loader.load(level_path);
  video.create_image(LEVELS_BASE_PATH + layers.background_layer.image_name);

  AsepriteLoader sprite_loader;
  player = Player(video, sprite_loader);
}

// TODO needs to take time step info
int Level::update(const NESInput &nes_input) {
  return LEVEL_ACTION_NONE;
}

// TODO WIP obviously
void Level::render(const VideoSDL &video) const {
  IntRect src(0, 0, 256, 240);
  IntRect dest(0, 0, 256, 240);
  video.render_image(LEVELS_BASE_PATH + layers.background_layer.image_name, src, dest);

  player.render(video);
}
