//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

TitleScreen::TitleScreen(GameSpec &game_spec, VideoSDL &video) : video(video) {
  backgroundImage = video.create_image("assets/sprites/title.png");
}

void TitleScreen::update(GameSpec &game_spec, float elapsed) {
  if (game_spec.input.start) {
    game_spec.view_mode = MODE_LOAD_LEVEL_1;
  }
}

void TitleScreen::render(const GameSpec &game_spec) const {
  video.render_texture(backgroundImage.get());
}
