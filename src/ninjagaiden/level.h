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
#include "camera.h"
//#include "json/json.h"
#include "control/nes_input_manager.h"
#include "video/video_sdl.h"

class Level
{
public:
  Level(LevelSpec &level_spec, VideoSDL &video);
  void update(LevelSpec &level_spec, const NESInput &nes_input, float elapsed);
  void render(const LevelSpec &level_spec) const;
private:
  Layers layers;
  Player player;
  UniqueTexture backgroundImage;
  VideoSDL &video;
  Camera camera;
};

//typedef std::unique_ptr<Level> UniqueLevel;

#endif
