//
//  level_view.h
//  Proto2
//
//  Created by Shaun West on 7/15/17.
//
//

#ifndef level_view_h
#define level_view_h

#include "util/log.h"
#include "video/video_sdl.h"
#include "control/nes_input_manager.h"

enum LevelAction {
  LEVEL_ACTION_NONE
};

class LevelView {
public:
  virtual LevelAction update(const NESInput &nes_input) {
    LOG(LOG_WARNING) << "View::update not implemented";
    return LEVEL_ACTION_NONE;
  };
  virtual void render(LevelSpec &level_spec, const VideoSDL &video) const {
    LOG(LOG_WARNING) << "View::render not implemented";
  };
};

typedef std::unique_ptr<LevelView> UniqueLevelView;

#endif
