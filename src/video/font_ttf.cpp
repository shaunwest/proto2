//
//  font_ttf.cpp
//  Proto2
//
//  Created by Shaun West on 7/10/17.
//
//

#include "font_ttf.h"

FontTTF::FontTTF() {}

FontTTF::FontTTF(std::string font_path) {
  if(!TTF_WasInit() && TTF_Init() == -1) {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
  }
  font = UniqueFont(TTF_OpenFont(font_path.c_str(), 16));
}

SDL_Surface * FontTTF::get_font(std::string str) const {
  return TTF_RenderUTF8_Blended(font.get(), str.c_str(), FONT_COLOR);
}
