//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

#define TITLE_IMAGE "assets/sprites/title.png"

TitleScreen::TitleScreen(VideoSDL &video) {
  video.create_image(TITLE_IMAGE);
}

int TitleScreen::update(const NESInput &nes_input) {
  if (nes_input.start) {
    return TITLE_ACTION_START;
  }

  return TITLE_ACTION_NONE;
}

void TitleScreen::render(const VideoSDL &video) const {
  video.render_image(TITLE_IMAGE);
}
