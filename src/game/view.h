//
//  view.h
//  Proto2
//
//  Created by Shaun West on 7/15/17.
//
//

#ifndef view_h
#define view_h

#include "util/log.h"
#include "video/video_sdl.h"
#include "control/nes_input_manager.h"

class View {
public:
  virtual int update(const NESInput &nes_input) {
    LOG(LOG_WARNING) << "View::update not implemented";
    return 0;
  };
  virtual void render(const VideoSDL &video) const {
    LOG(LOG_WARNING) << "View::render not implemented";
  };
};

typedef std::unique_ptr<View> UniqueView;

#endif /* screen_h */
