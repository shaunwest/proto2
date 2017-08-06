//
//  level.cpp
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#include "level.h"

#define LEVELS_BASE_PATH "assets/levels/"

Level::Level(LevelSpec &level_spec, VideoSDL &video) : video(video), player(level_spec.player_frameset, video) {
  backgroundImage = video.create_image2(LEVELS_BASE_PATH + level_spec.layers.background_layer.image_name);

  // TODO enemy objects will represent what's actually getting rendered on screen or is about to be.
  // So all enemy data objects will be loaded at the start, but only visible enemies will have active objects.
}

void Level::update(LevelSpec &level_spec, const NESInput &nes_input, float elapsed) {
  player.update(
      level_spec.player,
      level_spec.player_frameset,
      elapsed
  );
}

void Level::render(const LevelSpec &level_spec) const {
  IntRect src(0, 0, 256, 176);
  IntRect dest(0, 64, 256, 176);
  video.render_texture(backgroundImage.get(), src, dest);

  player.render(
      level_spec.player,
      level_spec.player_frameset
  );
}
