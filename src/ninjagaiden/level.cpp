//
//  level.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level.h"

#define LEVELS_BASE_PATH "assets/levels/"

Level::Level(LevelSpec &level_spec, VideoSDL &video) {
  backgroundImageId = video.create_image(LEVELS_BASE_PATH + level_spec.layers.background_layer.image_name);

  player = Player();

  // TODO enemy objects will represent what's actually getting rendered on screen or is about to be.
  // So all enemy data objects will be loaded at the start, but only visible enemies will have active objects.
}

// TODO needs to take time step info
LevelAction Level::update(const NESInput &nes_input) {
  return LEVEL_ACTION_NONE;
}

// TODO WIP obviously
void Level::render(LevelSpec &level_spec, const VideoSDL &video) const {
  IntRect src(0, 0, 256, 240);
  IntRect dest(0, 0, 256, 240);
  video.render_image(backgroundImageId, src, dest);
  player.render(level_spec.player, level_spec.sprite_framesets[level_spec.player.animation.frameset_id], video);
}
