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
#include "util/geom.h"
#include "screen.h"
#include "spec.h"

class TitleScreen : public Screen {
public:
  TitleScreen(GameSpec &game_spec, VideoSDL &video);
  void update(GameSpec &game_spec, float elapsed);
  void render(const GameSpec &game_spec) const;
private:
  VideoSDL &video;
  UniqueTexture background;
  Size backgroundSize;
};

typedef std::unique_ptr<TitleScreen, ScreenDeleter> UTitleScreen;

#endif
