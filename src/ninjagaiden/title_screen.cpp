//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

TitleScreen::TitleScreen(VideoSDL &video) : video(video) {
  background = video.create_image("assets/sprites/title.png");
  backgroundSize = video.get_texture_size(background.get());
}

void TitleScreen::update(ViewMode &view_mode, const NESInput &input, float elapsed) {
  if (input.start) {
    view_mode = MODE_LOAD_LEVEL_1;
  }
}

void TitleScreen::render() const {
  Recti size = { 0, 0, backgroundSize.width, backgroundSize.height };
  video.render_texture(background.get(), size, size);
}
