//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

TitleScreen::TitleScreen(VideoSDL &video) {
  //titleImageId = video.create_image("assets/sprites/title.png");
  backgroundImage = video.create_image2("assets/sprites/title.png");
}

ScreenAction TitleScreen::update(const NESInput &nes_input) {
  if (nes_input.start) {
    return SCREEN_ACTION_START;
  }

  return SCREEN_ACTION_NONE;
}

void TitleScreen::render(const VideoSDL &video) const {
  //video.render_image(titleImageId);
  video.render_texture(backgroundImage.get());
}
