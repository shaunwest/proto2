//
//  level_screen.cpp
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//

#include "level_screen.h"

LevelScreen::LevelScreen(GameSpec &game_spec, VideoSDL &video) :
  level(game_spec.level_spec, video), video(video) {}

void LevelScreen::update(GameSpec &game_spec, float elapsed) {
  level.update(game_spec.level_spec, game_spec.input, elapsed);
}

void LevelScreen::render(const GameSpec &game_spec) const {
  level.render(game_spec.level_spec);
}
