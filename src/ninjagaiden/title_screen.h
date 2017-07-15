//
//  title_screen.h
//  Proto2
//
//  Created by Shaun West on 6/12/17.
//
//

#ifndef title_screen_h
#define title_screen_h

#include "video/video_sdl.h"
#include "control/nes_input_manager.h"
#include "util/util.h"
#include "game/screen.h"

enum TitleAction {
  TITLE_NOACTION, TITLE_START
};

class TitleScreen : public Screen {
public:
  TitleScreen(VideoSDL &video);
  TitleAction update(const NESInput &nes_input);
  void render(const VideoSDL &video) const;
private:
  UniqueTexture background_texture;
};

#endif /* title_screen_h */
