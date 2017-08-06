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
#include "game_data.h"

class ScreenView {
public:
  virtual void update(GameSpec &game_spec, float elapsed) {
    LOG(LOG_WARNING) << "View::update not implemented";
  };
  virtual void render(const GameSpec &game_spec) const {
    LOG(LOG_WARNING) << "View::render not implemented";
  };
  virtual ~ScreenView() {
    LOG(LOG_DEBUG) << "View::~ScreenView called";
  };
};

struct ScreenViewDeleter
{
  void operator()(ScreenView *p) const {
    delete p;
    LOG(LOG_INFO) << "Screen View deleted";
  }
};

typedef std::unique_ptr<ScreenView, ScreenViewDeleter> UScreenView;

#endif
