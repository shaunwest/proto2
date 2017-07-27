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
#include "game/view.h"

enum TitleAction {
  TITLE_ACTION_NONE, TITLE_ACTION_START
};

class TitleScreen : public View {
public:
  TitleScreen(VideoSDL &video);
  int update(const NESInput &nes_input);
  void render(const VideoSDL &video) const;
private:
  //UniqueTexture background_texture;
};

typedef std::unique_ptr<TitleScreen> UniqueTitleScreen;

#endif /* title_screen_h */
