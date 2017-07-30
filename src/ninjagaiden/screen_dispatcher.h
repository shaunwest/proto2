//
//  screen_dispatcher.h
//  Proto2
//
//  Created by Shaun West on 7/24/17.
//
//

#ifndef screen_dispatcher_h
#define screen_dispatcher_h

#include "game/screen_view.h"
#include "control/nes_input_manager.h"
#include "video/video_sdl.h"

#include "title_screen.h"

enum ScreenDispatch
{
  SCREEN_DISPATCH_NONE, SCREEN_DISPATCH_START_GAME
};

class ScreenDispatcher
{
public:
  ScreenDispatcher(VideoSDL &video);
  ScreenDispatch update(ScreenId screen_id, const NESInput &input);
  // TODO can video be const? render?
  void render(ScreenId screen_id);
private:
  UniqueScreenView screen_view;
  VideoSDL &video;
};

#endif
