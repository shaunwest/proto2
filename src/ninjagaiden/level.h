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

#include "player.h"

#include "json/json.h"
#include "game/level_view.h"
#include "game/level_data.h"
#include "video/video_sdl.h"

class Level : public LevelView
{
public:
  Level(LevelSpec &level_spec, VideoSDL &video);
  LevelAction update(const NESInput &nes_input);
  void render(LevelSpec &level_spec, const VideoSDL &video) const;
private:
  Layers layers;
  Player player;
  int backgroundImageId;
};

typedef std::unique_ptr<Level> UniqueLevel;

#endif /* level_h */
