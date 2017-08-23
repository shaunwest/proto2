//
//  level_manager.h
//  Proto2
//
//  Created by Shaun West on 7/16/17.
//
//

#ifndef level_manager_h
#define level_manager_h

#include <iostream>

#include "objects/player_object.h"
#include "camera.h"
#include "control/nes_input_manager.h"
#include "video/video_sdl.h"

class LevelManager
{
public:
  LevelManager(Level &level, VideoSDL &video);
  void update(Level &level, const NESInput &nes_input, float elapsed);
  void render(const Level &level) const;
private:
  Layers layers;
  PlayerObject player_object;
  // TODO Sprites sprites;
  UniqueTexture backgroundImage;
  VideoSDL &video;
  Camera camera;
};

#endif
