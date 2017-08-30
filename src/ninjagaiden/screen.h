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
#include "ninjagaiden/game.h"
#include "control/nes_input_manager.h"

class Screen {
public:
  virtual void update(ViewMode &view_mode, const NESInput &input, float elapsed) {
    LOG(LOG_WARNING) << "Screen::update not implemented";
  };
  virtual void render() const {
    LOG(LOG_WARNING) << "Screen::render not implemented";
  };
  virtual ~Screen() {};
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
