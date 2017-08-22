//
//  screen.h
//  Proto2
//
//  Created by Shaun West on 7/15/17.
//
//

#ifndef screen_h
#define screen_h

#include "util/log.h"
#include "video/video_sdl.h"
#include "spec.h"

class Screen {
public:
  virtual void update(GameSpec &game_spec, float elapsed) {
    LOG(LOG_WARNING) << "View::update not implemented";
  };
  virtual void render(const GameSpec &game_spec) const {
    LOG(LOG_WARNING) << "View::render not implemented";
  };
  virtual ~Screen() {
    LOG(LOG_DEBUG) << "View::~ScreenView called";
  };
};

struct ScreenDeleter
{
  void operator()(Screen *p) const {
    delete p;
    LOG(LOG_INFO) << "Screen deleted";
  }
};

typedef std::unique_ptr<Screen, ScreenDeleter> UScreen;

#endif
