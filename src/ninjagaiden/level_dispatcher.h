//
//  level_dispatcher.h
//  Proto2
//
//  Created by Shaun West on 7/29/17.
//
//

#ifndef level_dispatcher_h
#define level_dispatcher_h

#include "control/nes_input_manager.h"
#include "video/video_sdl.h"
#include "loader/tiled_loader.h"
#include "loader/aseprite_loader.h"
//#include "game/level_view.h"
#include "level.h"

enum LevelDispatch
{
  LEVEL_DISPATCH_NONE
};

class LevelDispatcher
{
public:
  LevelDispatcher(VideoSDL &video);
  LevelDispatch update(LevelSpec &level_spec, const NESInput &input);
  // TODO can any of this be const?
  void render(LevelSpec &level_spec);
private:
  UniqueLevelView level_view; // does this even need cleanup???? Why pointer?
  TiledLoader level_loader;
  AsepriteLoader sprite_loader;
  VideoSDL &video;
};

#endif
