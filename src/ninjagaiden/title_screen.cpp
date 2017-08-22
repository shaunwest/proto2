//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

TitleScreen::TitleScreen(GameSpec &game_spec, VideoSDL &video) : video(video) {
  background = video.create_image("assets/sprites/title.png");
  backgroundSize = video.get_texture_size(background.get());
}

void TitleScreen::update(GameSpec &game_spec, float elapsed) {
  if (game_spec.input.start) {
    game_spec.view_mode = MODE_LOAD_LEVEL_1;
  }
}

void TitleScreen::render(const GameSpec &game_spec) const {
  Recti size = { 0, 0, backgroundSize.width, backgroundSize.height };
  video.render_texture(background.get(), size, size);
}
