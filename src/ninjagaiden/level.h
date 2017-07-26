//
//  level.h
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#ifndef level_h
#define level_h

#include <iostream>

#include "json/json.h"
#include "game/view.h"
#include "video/video_sdl.h"
#include "loader/tiled_loader.h"

enum LevelAction {
  LEVEL_ACTION_NONE
};

class Level : public View
{
public:
  Level(std::string level_path, VideoSDL &video, TiledLoader &level_loader);
  int update(const NESInput &nes_input);
  void render(const VideoSDL &video) const;
private:
  Layers layers;
};

typedef std::unique_ptr<Level> UniqueLevel;

#endif /* level_h */
