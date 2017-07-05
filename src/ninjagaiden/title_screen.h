//
//  title_screen.h
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#ifndef title_screen_h
#define title_screen_h

#include "video/renderer_sdl.h"
#include "control/nes_input_manager.h"
#include "util/util.h"

enum TitleAction {
  TITLE_NOACTION, TITLE_START
};

class TitleScreen {
public:
  TitleScreen(const RendererSDL &renderer);
  TitleAction update(const NESInput &nes_input);
  void render(const RendererSDL &renderer);
private:
  UniqueTexture background_texture;
  Size size;
};

#endif /* title_screen_h */
