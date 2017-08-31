//
//  level_manager.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level_manager.h"
#include "object/enemy_object.h"

#define LEVELS_BASE_PATH "assets/levels/"

LevelManager::LevelManager(Level level, VideoSDL &video) :
  level(level),
  player_object(this->level.player, this->level.sprite_framesets[0], video),
  video(video),
  camera_manager(this->level.camera) {
  backgroundImage = video.create_image(LEVELS_BASE_PATH + this->level.layers.background.image_name);

  // Should only nearby sprites be "active"?
  for (auto &sprite : this->level.layers.sprite.sprites) {
    if (sprite.type == "enemy") {
      LOG(LOG_DEBUG) << "added enemy" << " Frameset id" << sprite.frameset_id;
      sprite_objects.push_back(
          new EnemyObject(sprite, this->level.sprite_framesets[sprite.frameset_id], video));
    }
  }
}

LevelManager::~LevelManager() {
  for (auto sprite : sprite_objects) {
    delete sprite;
  }
  sprite_objects.clear();
}

void LevelManager::update(const NESInput &nes_input, float elapsed) {
  player_object.update(level.layers, nes_input, elapsed);
  camera_manager.update(level.player);

  for (auto sprite_object : sprite_objects) {
    sprite_object->update(level.layers, elapsed);
  }
}

void LevelManager::render() const {
  // Background
  Recti src(
    level.camera.position.x,
    level.camera.position.y,
    level.camera.viewport.width,
    level.camera.viewport.height
  );

  // Position below stats area
  Recti dest(
    level.layers.background.position.x,
    level.layers.background.position.y,
    level.camera.viewport.width,
    level.camera.viewport.height
  );

  video.render_texture(backgroundImage.get(), src, dest);

  // Player
  player_object.render(level.camera);

  // Sprites
  for (auto sprite_object : sprite_objects) {
    sprite_object->render(level.camera);
  }
}
