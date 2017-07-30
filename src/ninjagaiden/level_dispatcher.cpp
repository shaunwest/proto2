//
//  level_dispatcher.cpp
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//

#include "level_dispatcher.h"

LevelDispatcher::LevelDispatcher(VideoSDL &video) : video(video) {}

LevelDispatch LevelDispatcher::update(LevelSpec &level_spec, const NESInput &input) {
  switch (level_spec.level_id) {
    case LEVEL_1: {
      if (level_view == nullptr) {
        level_spec.layers = level_loader.load("levels/level1_1.json");
        // TODO how are these frameset ids going to work?
        level_spec.sprite_framesets[0] = sprite_loader.load("assets/sprites/ryu.json", video);
        level_view = UniqueLevel(new Level(level_spec, video));
      }

      LevelAction action = level_view->update(input);

      switch (action) {
        case LEVEL_ACTION_NONE:
          return LEVEL_DISPATCH_NONE;
      }

      break;
    }
  }
}

void LevelDispatcher::render(LevelSpec &level_spec) {
  if (level_view != nullptr) {
    level_view->render(level_spec, video);
  }
}
