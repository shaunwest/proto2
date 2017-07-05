//
//  title_screen.cpp
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#include "title_screen.h"

TitleScreen::TitleScreen(const RendererSDL &renderer) {
  background_texture = renderer.create_texture("title.png");
  SDL_QueryTexture(background_texture.get(), NULL, NULL, &size.width, &size.height);
}

TitleAction TitleScreen::update(const NESInput &nes_input) {
  if (nes_input.start) {
    return TITLE_START;
  }
  
  return TITLE_NOACTION;
}

void TitleScreen::render(const RendererSDL &renderer) {
  SDL_Rect src = {0, 0, size.width, size.height};
  SDL_Rect dest = {0, 0, size.width, size.height};
  renderer.render_texture(background_texture.get(), src, dest);
  
}
