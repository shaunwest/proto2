//
//  level_manager.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level_manager.h"
#include "objects/enemy_object.h"

#define LEVELS_BASE_PATH "assets/levels/"

LevelManager::LevelManager(Level level, VideoSDL &video) :
  level(level),
  player_object(this->level.player, this->level.sprite_framesets[0], video),
  video(video),
  camera_manager(this->level.camera) {
  backgroundImage = video.create_image(LEVELS_BASE_PATH + this->level.layers.background_layer.image_name);

  // Should only nearby sprites be "active"?
  /*
  for (auto sprite : level.layers.sprite_layer.sprites) {
    if (sprite.type == "enemy") {
      LOG(LOG_DEBUG) << "added enemy!!!!";
      sprite_objects.push_back(EnemyObject(sprite, sprite_framesets[sprite.frameset_id], video));
    }
  }
  */
}

void LevelManager::update(const NESInput &nes_input, float elapsed) {
  player_object.update(level.layers, nes_input, elapsed);
  camera_manager.update(level.player);

  //for (auto sprite : sprites) {
    // TODO update sprite
  //}
}

void LevelManager::render() const {
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
  player_object.render(level.camera);
}
