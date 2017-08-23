//
//  level_screen.cpp
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//

#include "level_screen.h"

LevelScreen::LevelScreen(Game &game, VideoSDL &video) :
  levelManager(game.level, video), video(video) {}

void LevelScreen::update(Game &game, float elapsed) {
  levelManager.update(game.level, game.input, elapsed);
}

void LevelScreen::render(const Game &game) const {
  levelManager.render(game.level);
}
