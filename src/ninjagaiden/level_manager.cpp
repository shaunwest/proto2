//
//  level_manager.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level_manager.h"

#define LEVELS_BASE_PATH "assets/levels/"

LevelManager::LevelManager(Level &level, VideoSDL &video)
  : video(video), player_object(level.player_frameset, video) {
  backgroundImage = video.create_image(LEVELS_BASE_PATH + level.layers.background_layer.image_name);
  // TODO enemy objects will represent what's actually getting rendered on screen or is about to be.
  // So all enemy data objects will be loaded at the start, but only visible enemies will have active objects.
  for (auto sprite : level.layers.sprite_layer.sprites) {
    // TODO Load sprite based on its type. Which means we need to use the "type" property in Tiled
    // TODO pass sprite_spec to sprite object
  }
}

void LevelManager::update(Level &level, const NESInput &nes_input, float elapsed) {
  player_object.update(level, nes_input, elapsed);
  camera.update(level.camera, level.player);

  //for (auto sprite : sprites) {
    // TODO update sprite
  //}
}

void LevelManager::render(const Level &level) const {
  // Background
  Recti src(
      level.camera.position.x,
      level.camera.position.y,
      level.camera.viewport.width,
      level.camera.viewport.height
  );

  Recti dest(
      0,
      64,
      level.camera.viewport.width,
      level.camera.viewport.height
  );

  video.render_texture(backgroundImage.get(), src, dest);

  // Player
  player_object.render(
      level.player,
      level.player_frameset,
      level.camera
  );
}
