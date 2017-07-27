//
//  font_ttf.h
//  Proto2
//
//  Created by Shaun West on 7/10/17.
//
//

#ifndef font_ttf_h
#define font_ttf_h

#define FONT_COLOR  {255, 255, 255}

#include "SDL_ttf.h"

#include <iostream>

#include "util/log.h"

struct FontDeleter
{
  void operator()(TTF_Font *f) const {
    TTF_CloseFont(f);
    TTF_Quit();
    LOG(LOG_INFO) << "TTF Font Closed";
  }
};

typedef std::unique_ptr<TTF_Font, FontDeleter> UniqueFont;

class FontTTF
{
public:
  FontTTF();
  FontTTF(std::string font_path);
  SDL_Surface * get_font(std::string str) const;
private:
  UniqueFont font;
};

#endif /* font_ttf_h */
