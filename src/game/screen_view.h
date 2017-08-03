//
//  screen_view.h
//  Proto2
//
//  Created by Shaun West on 7/15/17.
//
//

#ifndef screen_view_h
#define screen_view_h

#include "util/log.h"
#include "video/video_sdl.h"
#include "control/nes_input_manager.h"

enum ScreenAction {
  SCREEN_ACTION_NONE,
  SCREEN_ACTION_START
};

enum ScreenId {
  SCREEN_TITLE
};

class ScreenView {
public:
  virtual ScreenAction update(const NESInput &nes_input) {
    LOG(LOG_WARNING) << "View::update not implemented";
    return SCREEN_ACTION_NONE;
  };
  virtual void render(const VideoSDL &video) const {
    LOG(LOG_WARNING) << "View::render not implemented";
  };
};

/*
struct Deleter2
{
  void operator()(ScreenView *p) const {
    LOG(LOG_INFO) << "Screen View deleted";
  }
};

typedef std::unique_ptr<ScreenView, Deleter2> UniqueScreenView;
*/
#endif
